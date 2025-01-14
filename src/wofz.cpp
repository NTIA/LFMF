/** @file wofz.cpp
 * Implements a function to calculate the Faddeeva function @f$ W(z) @f$.
 */

#include "LFMF.h"

#include <cmath>    // for abs, cos, exp, pow, sin, sqrt
#include <complex>  // for std::complex

namespace ITS {
namespace Propagation {
namespace LFMF {

/*******************************************************************************
 * This function computes the Faddeeva function 
 * @f$ W(z) = e^{-z^2} \mathrm{erfc}(-iz) @f$.
 * 
 * Given a complex input argument @f$ z @f$, this function computes the value of
 * the above equation, in which @f$\mathrm{erfc}@f$ is the complex complementary
 * error function and @f$ i @f$ is @f$ \sqrt{-1} @f$. 
 * 
 * The basis for this function is Algorithm 680, Collected Algorithms from ACM,
 * (reference provided below). This version of the function accepts a single
 * complex input argument `z` and returns a single complex output. The following
 * note is restated from the original implementation's description:
 * 
 * @note The accuracy of the algorithm for @f$ z @f$ in the 1st and 2nd
 * quadrant is 14 significant digits; in the 3rd and 4th it is 13 significant
 * digits outside a circular region with radius 0.126 around a zero of the function.
 * 
 * @param[in] z  Input argument
 * @return       The desired @f$ W(z)_ @f$ function calculated at `z`
 * 
 * **Lineage**
 *   - The original FORTRAN implementation was translated to C/C++ by
 *     I. Stevanovic (OFCOM CH).
 *   - Direct comparisons of `double` values with `==` were removed by C. Heroy,
 *     who implemented `AlmostEqualRelative()`.
 * 
 * **References**
 *   - Algorithm 680, Collected Algorithms from ACM, Transactions of Mathematical
 *     Software, Vol. 16, No. 1, pp. 47: https://doi.org/10.1145/77626.77630
 ******************************************************************************/
std::complex<double> wofz(const std::complex<double> z) {
    constexpr double FACTOR = 1.12837916709551257388;
    constexpr double RMAXREAL = 0.5E+154;
    constexpr double RMAXEXP = 708.503061461606E0;
    constexpr double RMAXGONI = 3.53711887601422E+15;

    const double XI = z.real();
    const double YI = z.imag();

    const double XABS = std::abs(XI);
    const double YABS = std::abs(YI);
    const double X = XABS / 6.3;
    const double Y = YABS / 4.4;

    std::complex<double> w;

    double XSUM, YSUM, U, V, XAUX, U1, V1, DAUX, U2, V2, H, H2, KAPN;
    double QLAMBDA, RX, RY, TX, TY, SX, SY, W1, CC;

    int NU, NP1;

    // This condition protects `QRHO = (X**2 + Y**2)` against overflow
    if ((XABS > RMAXREAL) || (YABS > RMAXREAL)) {
        w = std::complex<double>(0.0, 0.0);
        return w;
    }

    double QRHO = X * X + Y * Y;

    const double XABSQ = std::pow(XABS, 2.0);
    double XQUAD = XABSQ - std::pow(YABS, 2.0);
    const double YQUAD = 2 * XABS * YABS;

    const bool A = (QRHO < 0.085264E0);

    if (A) {
        // If (QRHO < 0.085264) then the Faddeeva-function is evaluated using a
        // power-series (Abramowitz/Stegun, Eqn 7.1.5, p.297).
        // N is the minimum number of terms needed to obtain the required accuracy.
        QRHO = (1 - 0.85 * Y) * std::sqrt(QRHO);
        const int N = (int)(6 + 72 * QRHO);
        int J = 2 * N + 1;
        XSUM = 1.0 / J;
        YSUM = 0.0;
        for (int I = N; I > 0; I--) {
            J = J - 2;
            XAUX = (XSUM * XQUAD - YSUM * YQUAD) / I;
            YSUM = (XSUM * YQUAD + YSUM * XQUAD) / I;
            XSUM = XAUX + 1.0 / J;
        }
        U1 = -FACTOR * (XSUM * YABS + YSUM * XABS) + 1.0;
        V1 = FACTOR * (XSUM * XABS - YSUM * YABS);
        DAUX = std::exp(-XQUAD);
        U2 = DAUX * std::cos(YQUAD);
        V2 = -DAUX * std::sin(YQUAD);

        U = U1 * U2 - V1 * V2;
        V = U1 * V2 + V1 * U2;
    } else {
        if (QRHO > 1.0) {
            // If (QRHO > 1.O) then W(Z) is evaluated using the Laplace continued fraction
            // NU is the minimum number of terms needed to obtain the required accuracy.
            H = 0.0;
            KAPN = 0;
            QRHO = std::sqrt(QRHO);
            NU = (int)(3 + (1442 / (26 * QRHO + 77)));
        } else {
            // If ((QRHO > 0.085264) AND (QRHO < 1.0)) then W(Z) is evaluated by a
            // truncated Taylor expansion, where the Laplace continued fraction is
            // used to calculate the derivatives of W(Z)
            // KAPN is the minimum number of terms in the Taylor expansion needed to
            // obtain the required accuracy.
            // NU is the number of terms of the continued fraction needed to calculate
            // the derivatives with the required accuracy.
            QRHO = (1 - Y) * std::sqrt(1 - QRHO);
            H = 1.88 * QRHO;
            H2 = 2 * H;
            KAPN = (int)(7 + 34 * QRHO);
            NU = (int)(16 + 26 * QRHO);
        }

        const bool B = (H > 0.0);

        if (B) {
            QLAMBDA = std::pow(H2, KAPN);
        } else {
            QLAMBDA = 0.0;  // Not used, initialization avoids compile warning
        }

        RX = 0.0;
        RY = 0.0;
        SX = 0.0;
        SY = 0.0;

        for (int N = NU; N >= 0; N--) {
            NP1 = N + 1;
            TX = YABS + H + NP1 * RX;
            TY = XABS - NP1 * RY;
            CC = 0.5 / (TX * TX + TY * TY);
            RX = CC * TX;
            RY = CC * TY;
            if ((B) && (N <= KAPN)) {
                TX = QLAMBDA + SX;
                SX = RX * TX - RY * SY;
                SY = RY * TX + RX * SY;
                QLAMBDA = QLAMBDA / H2;
            }
        }

        if (AlmostEqualRelative(H, 0.0)) {
            U = FACTOR * RX;
            V = FACTOR * RY;
        } else {
            U = FACTOR * SX;
            V = FACTOR * SY;
        }

        if (AlmostEqualRelative(YABS, 0.0)) {
            U = std::exp(-XABS * XABS);
        }
    }

    // EVALUATION OF W(Z) IN THE OTHER QUADRANTS


    if (YI < 0.0) {
        if (A) {
            U2 = 2 * U2;
            V2 = 2 * V2;
        } else {
            XQUAD = -XQUAD;

            // This condition protects `2*EXP(-Z**2)` against overflow
            if ((YQUAD > RMAXGONI) || (XQUAD > RMAXEXP)) {
                w = std::complex<double>(0.0, 0.0);
                return w;
            }

            W1 = 2 * std::exp(XQUAD);
            U2 = W1 * std::cos(YQUAD);
            V2 = -W1 * std::sin(YQUAD);
        }

        U = U2 - U;
        V = V2 - V;
        if (XI > 0.0) {
            V = -V;
        }
    } else {
        if (XI < 0.0) {
            V = -V;
        }
    }

    w = std::complex<double>(U, V);
    return w;
}

}  // namespace LFMF
}  // namespace Propagation
}  // namespace ITS