/** @file ResidueSeries.cpp
 * Implements a function to calculate the ground wave field strength.
 */

#include "LFMF.h"

#include <cmath>    // for abs, exp, sqrt
#include <complex>  // for std::complex

namespace ITS {
namespace Propagation {
namespace LFMF {

/*******************************************************************************
 * Calculates the groundwave field strength using the Residue Series method
 *
 * @param[in] k           Wavenumber, in rad/km
 * @param[in] h_1__km     Height of the lower antenna, in km
 * @param[in] h_2__km     Height of the higher antenna, in km
 * @param[in] nu          Intermediate value, pow(a_e__km * k / 2.0, THIRD);
 * @param[in] theta__rad  Angular distance of path, in radians
 * @param[in] q           Intermediate value -j*nu*delta
 * @return                Normalized field strength in mV/m
 ******************************************************************************/
double ResidueSeries(
    const double k,
    const double h_1__km,
    const double h_2__km,
    const double nu,
    const double theta__rad,
    const std::complex<double> q
) {
    std::complex<double> DW2[200], W2[200];  // dummy variables
    std::complex<double> G;

    constexpr std::complex<double> j = std::complex<double>(0.0, 1.0);

    std::complex<double> T[200], W1[200], W[200];
    double yHigh, yLow;

    std::complex<double> GW
        = std::complex<double>(0.0, 0.0);  // initial ground wave

    // Associated argument for the height-gain function H_1[h_1]
    yHigh = k * h_2__km / nu;

    // Associated argument for the height-gain function H_2[h_2]
    yLow = k * h_1__km / nu;

    const double x = nu * theta__rad;

    for (int i = 0; i < 200; i++) {
        T[i] = WiRoot(
            i + 1, &DW2[i], q, &W2[i], WONE, WAIT
        );  // find the (i+1)th root of Airy function for given q
        W1[i] = Airy(T[i], WONE, WAIT);  // Airy function of (i)th root

        if (h_1__km > 0) {
            W[i]
                = Airy(T[i] - yLow, WONE, WAIT)
                / W1[i];  //height gain function H_1(h_1) eqn.(22) from NTIA report 99-368

            if (h_2__km > 0)
                W[i] *= Airy(T[i] - yHigh, WONE, WAIT)
                      / W1[i];  //H_1(h_1)*H_1(h_2)
        } else if (h_2__km > 0)
            W[i] = Airy(T[i] - yHigh, WONE, WAIT) / W1[i];
        else
            W[i] = std::complex<double>(1, 0);

        // W[i] is the coefficient of the distance factor for the i-th
        W[i]
            /= (T[i] - (q * q)
            );  // H_1(h_1)*H_1(h_2)/(t_i-q^2) eqn.26 from NTIA report 99-368
        G = W[i]
          * std::exp(
                -1.0 * j * x * T[i]
          );      // sum of exp(-j*x*t_i)*W[i] eqn.26 from NTIA report 99-368
        GW += G;  // sum the series

        if (i != 0) {
            //if ((abs((GW * GW).real()) + (abs((GW * GW).imag()))) == 0.0) {     // when the ground wave is too small close to 0.
            // Replaced with AlmostEqualRelative
            if (AlmostEqualRelative(
                    (std::abs((GW * GW).real()) + (std::abs((GW * GW).imag()))),
                    0.0,
                    0.9
                )) {
                return 0;  // end the loop and output E = 0
            } else if (((std::abs((G / GW).real()))
                        + (std::abs((G / GW).imag())))
                       < 0.0005)  // when the new G is too small compared to its series sum
            {
                // when the new G is too small compared to its series sum, it's ok to stop the loop
                // because adding small number to a significant big one doesn't affect their sum.
                //J1 = i;
                break;
            }
        }
    }

    // field strength.  complex<double>(sqrt(PI/2)) = sqrt(pi)*e(-j*PI/4)
    const std::complex<double> Ew
        = std::sqrt(x)
        * std::complex<double>(std::sqrt(PI / 2), -std::sqrt(PI / 2)) * GW;

    double E_gw = std::abs(Ew);  // take the magnitude of the result

    return E_gw;
}

}  // namespace LFMF
}  // namespace Propagation
}  // namespace ITS