/** @file LFMF.cpp
 * Implements the model from ITS.Propagation.LFMF.
 */

#include "LFMF.h"

#include <cmath>    // for cbrt, exp, fabs, log10, pow, sqrt
#include <complex>  // for std::complex

namespace ITS {
namespace Propagation {
namespace LFMF {

/*******************************************************************************
 * Compute the LFMF propagation prediction
 *
 * @param[in]  h_tx__meter  Height of the transmitter, in meter
 * @param[in]  h_rx__meter  Height of the receiver, in meter
 * @param[in]  f__mhz       Frequency, in MHz
 * @param[in]  P_tx__watt   Transmitter power, in watts
 * @param[in]  N_s          Surface refractivity, in N-Units
 * @param[in]  d__km        Path distance, in km
 * @param[in]  epsilon      Relative permittivity
 * @param[in]  sigma        Conductivity
 * @param[in]  pol          Polarization: 0 = Horizontal, 1 = Vertical
 * @param[out] result       Result structure
 * @return                  Error code
 ******************************************************************************/
ReturnCode LFMF(
    const double h_tx__meter,
    const double h_rx__meter,
    const double f__mhz,
    const double P_tx__watt,
    const double N_s,
    const double d__km,
    const double epsilon,
    const double sigma,
    const int pol,
    Result &result
) {
    ReturnCode rtn = ValidatePolarization(pol);
    if (rtn != SUCCESS)
        return rtn;

    return LFMF_CPP(
        h_tx__meter,
        h_rx__meter,
        f__mhz,
        P_tx__watt,
        N_s,
        d__km,
        epsilon,
        sigma,
        static_cast<Polarization>(pol),
        result
    );
}

/*******************************************************************************
 * Compute the LFMF propagation prediction
 *
 * @param[in]  h_tx__meter  Height of the transmitter, in meter
 * @param[in]  h_rx__meter  Height of the receiver, in meter
 * @param[in]  f__mhz       Frequency, in MHz
 * @param[in]  P_tx__watt   Transmitter power, in watts
 * @param[in]  N_s          Surface refractivity, in N-Units
 * @param[in]  d__km        Path distance, in km
 * @param[in]  epsilon      Relative permittivity
 * @param[in]  sigma        Conductivity
 * @param[in]  pol          Polarization: 0 = Horizontal, 1 = Vertical
 * @param[out] result       Result structure
 * @return                  Error code
 * 
 * @see ITS::Propagation::LFMF::Polarization
 * @see ITS::Propagation::LFMF::Result
 ******************************************************************************/
ReturnCode LFMF_CPP(
    const double h_tx__meter,
    const double h_rx__meter,
    const double f__mhz,
    const double P_tx__watt,
    const double N_s,
    const double d__km,
    const double epsilon,
    const double sigma,
    const Polarization pol,
    Result &result
) {
    ReturnCode rtn = ValidateInput(
        h_tx__meter, h_rx__meter, f__mhz, P_tx__watt, N_s, d__km, epsilon, sigma
    );
    if (rtn != SUCCESS)
        return rtn;

    // Create the complex value j since this was written by electrical engineers
    constexpr std::complex<double> j = std::complex<double>(0.0, 1.0);

    const double f__hz = f__mhz * 1e6;
    const double lambda__meter = C / f__hz;  // wavelength, in meters

    const double h_1__km
        = std::min(h_tx__meter, h_rx__meter) / 1000;  // lower antenna, in km
    const double h_2__km
        = std::max(h_tx__meter, h_rx__meter) / 1000;  // higher antenna, in km

    const double a_e__km = a_0__km * 1
                         / (1 - 0.04665 * std::exp(0.005577 * N_s)
                         );  // effective earth radius, in km

    const double theta__rad = d__km / a_e__km;

    const double k = 2.0 * PI * 1000 / lambda__meter;  // wavenumber, in rad/km
    const double nu = std::cbrt(a_e__km * k / 2.0);    // Intermediate value nu

    // dielectric ground constant. See Eq (17) DeMinco 99-368
    const std::complex<double> eta
        = std::complex<double>(epsilon, -sigma / (epsilon_0 * 2 * PI * f__hz));

    // Find the surface impedance, DeMinco 99-368 Eqn (15)
    std::complex<double> delta = std::sqrt(eta - 1.0);
    if (pol == Polarization::VERTICAL)
        delta /= eta;

    const std::complex<double> q = -nu * j * delta;  // intermediate value q

    // Determine which smooth earth method is used; SG3 Groundwave Handbook, Eq 15
    const double d_test__km = 80 / std::cbrt(f__mhz);

    double E_gw;
    if (d__km < d_test__km) {
        E_gw = FlatEarthCurveCorrection(
            delta, q, h_1__km, h_2__km, d__km, k, a_e__km
        );
        result.method = SolutionMethod::FLAT_EARTH_CURVE;
    } else {
        E_gw = ResidueSeries(k, h_1__km, h_2__km, nu, theta__rad, q);
        result.method = SolutionMethod::RESIDUE_SERIES;
    }

    // Antenna gains
    constexpr double G_tx__dbi = 4.77;
    constexpr double G_rx__dbi = 4.77;

    const double G_tx = std::pow(10, G_tx__dbi / 10);

    // Un-normalize the electric field strength
    const double E_0 = std::sqrt(ETA * (P_tx__watt * G_tx) / (4.0 * PI))
                     / d__km;  // V/km or mV/m
    E_gw = E_gw * E_0;

    // Calculate the basic transmission loss using (derived using Friis Transmission Equation with Electric Field Strength)
    //      Pt     Gt * Pt * ETA * 4*PI * f^2
    // L = ---- = ---------------------------  and convert to dB
    //      Pr            E^2 * c^2
    // with all values entered using base units: watts, Hz, and V/m
    // basic transmission loss is not a function of power/gain, but since electric field strength E_gw is a function of (Gt * Pt),
    //    and Lbtl is a function of 1/E_gw, we add in (Gt * Pt) to remove its effects
    result.A_btl__db = 10 * std::log10(P_tx__watt * G_tx)
                      + 10 * std::log10(ETA * 4 * PI) + 20 * std::log10(f__hz)
                      - 20 * std::log10(E_gw / 1000) - 20 * std::log10(C);

    // the 60 constant comes from converting field strength from mV/m to dB(uV/m) thus 20*log10(1e3)
    result.E_dBuVm = 60 + 20 * std::log10(E_gw);

    // Note power is a function of frequency.  42.8 comes from MHz to hz, power in dBm, and the remainder from
    // the collection of constants in the derivation of the below equation.
    result.P_rx__dbm
        = result.E_dBuVm + G_rx__dbi - 20.0 * std::log10(f__hz) + 42.8;

    return SUCCESS;
}

/*******************************************************************************
 * Relative epsilon comparisons method
 *
 * @param[in] A           First double to compare
 * @param[in] B           Second double to compare
 * @param[in] maxRelDiff  Maximum relative difference, defaults to DBL_EPSILON
 * @return                If it is equal of the two doubles
 ******************************************************************************/
bool AlmostEqualRelative(
    const double A, const double B, const double maxRelDiff
) {
    // Calculate the difference.
    const double diff = std::fabs(A - B);
    const double absA = std::fabs(A);
    const double absB = std::fabs(B);
    // Find the largest
    const double largest = (absB > absA) ? absB : absA;

    if (diff <= largest * maxRelDiff)
        return true;
    return false;
}

}  // namespace LFMF
}  // namespace Propagation
}  // namespace ITS