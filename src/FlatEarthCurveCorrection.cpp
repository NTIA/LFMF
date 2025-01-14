/** @file FlatEarthCurveCorrection.cpp
 * Calculates the groundwave using the flat Earth approximation with curvature correction.
 */

#include "LFMF.h"

#include <cmath>    // for abs, exp, pow, sqrt
#include <complex>  // for std::complex

namespace ITS {
namespace Propagation {
namespace LFMF {

/*******************************************************************************
 * Calculates the groundwave field strength using the flat Earth approximation
 * with curvature correction.
 *
 * References:
 *     - NTIA Report 99-368 "Medium Frequency Propagation Prediction Techniques
 *       and Antenna Modeling for Intelligent Transportation Systems (ITS)
 *       Broadcast Applications", Nicholas DeMinco.  Eq (31)
 *     - J. Wait, "Radiation From a Vertical Antenna Over a Curved Stratified
 *       Ground", Journal of Research of the National Bureau of Standards Vol 56,
 *       No. 4, April 1956 Research Paper 2671
 *
 * @param[in] delta    Surface impedance
 * @param[in] q        Intermediate value -j*nu*delta
 * @param[in] h_1__km  Height of the higher antenna, in km
 * @param[in] h_2__km  Height of the lower antenna, in km
 * @param[in] d__km    Path distance, in km
 * @param[in] k        Wavenumber, in rad/km
 * @param[in] a_e__km  Effective earth radius, in km
 * @return             Normalized field strength in mV/m
 ******************************************************************************/
double FlatEarthCurveCorrection(
    const std::complex<double> delta,
    const std::complex<double> q,
    const double h_1__km,
    const double h_2__km,
    const double d__km,
    const double k,
    const double a_e__km
) {
    const std::complex<double> j = std::complex<double>(0.0, 1.0);

    // In order for the wofz() function to be used both here and in gwfe()
    // the argument, qi, has to be defined correctly. The following is how
    // it is done in the original GWFEC.FOR
    const std::complex<double> qi
        = (-0.5 + j * 0.5) * std::sqrt(k * d__km) * delta;
    const std::complex<double> p = qi * qi;

    const std::complex<double> p2 = std::pow(p, 2);
    const std::complex<double> q3 = std::pow(q, 3);
    const std::complex<double> q6 = std::pow(q, 6);
    const std::complex<double> q9 = std::pow(q, 9);

    std::complex<double> fofx;

    if (std::abs(q) > 0.1) {
        // Find F(p) Eqn (32) NTIA Report 99-368
        std::complex<double> Fofp = 1.0 + std::sqrt(PI) * j * qi * wofz(qi);

        // Calculate f(x) which is the normalized electric field, E_ratio; Eqn (31) NTIA Report 99-368
        fofx = Fofp
             + (1.0 - j * std::sqrt(PI * p) - (1.0 + 2.0 * p) * Fofp)
                   / (4.0 * q3);
        fofx = fofx
             + (1.0 - j * std::sqrt(PI * p) * (1.0 - p) - 2.0 * p
                + 5.0 * p2 / 6.0 + (p2 / 2.0 - 1.0) * Fofp)
                   / (4.0 * q6);
    } else {
        std::complex<double> A[10];

        // [Deminco, Eq 30]
        A[0] = 1.0;
        A[1] = -j * std::sqrt(PI);
        A[2] = -2.0;
        A[3] = j * std::sqrt(PI) * (1.0 + 1.0 / (4.0 * q3));
        A[4] = 4.0 / 3.0 * (1.0 + 1.0 / (2.0 * q3));
        A[5] = -j * std::sqrt(PI) / 4.0 * (1.0 + 3.0 / (4.0 * q3));
        A[6] = -8.0 / 15.0 * (1.0 + 1.0 / q3 + 7.0 / (32.0 * q6));
        A[7] = j * std::sqrt(PI) / 6.0
             * (1.0 + 5.0 / (4.0 * q3) + 27.0 / (32.0 * q6));
        A[8] = 16.0 / 105.0 * (1.0 + 3.0 / (2.0 * q3) + 27.0 / (32.0 * q6));
        A[9] = -j * std::sqrt(PI) / 24.0
             * (1.0 + 7.0 / (4.0 * q3) + 5.0 / (4.0 * q6) + 21.0 / (64.0 * q9));

        const double x
            = d__km / a_e__km * std::pow(k * a_e__km / 2.0, (1.0 / 3.0));

        fofx = 0.0 + j * 0.0;

        // [Deminco, Eq 28]
        for (int ii = 0; ii < 10; ii++) {
            fofx = fofx
                 + A[ii]
                       * std::pow(
                           std::exp(j * PI / 4.0) * q * std::pow(x, 1.0 / 2.0),
                           ii
                       );
        }
    }

    // Now find the final normalized field strength from f(x) and the height-gain function for each antenna
    // A height-gain function for an antenna is expressed as two terms of a Taylor series
    // (See DeMinco NTIA Report 99-368 Aug 1999
    // "Medium Frequency Propagation Prediction Techniques and
    // Antenna Modeling for Intelligent Transportation Systems (ITS) Broadcast Applications"
    // Equation 36)
    const double E_gw__mVm = std::abs(
        fofx * (1.0 + j * k * h_2__km * delta) * (1.0 + j * k * h_1__km * delta)
    );

    return E_gw__mVm;
}

}  // namespace LFMF
}  // namespace Propagation
}  // namespace ITS