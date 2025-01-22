/** @file WiRoot.cpp
 * Implements a function to find roots of equations involving Airy functions.
 */

#include "LFMF.h"

#include <cmath>      // for abs, cos, pow, sin
#include <complex>    // for std::complex
#include <sstream>    // for std::ostringstream
#include <stdexcept>  // for std::invalid_argument, std::runtime_error

namespace ITS {
namespace Propagation {
namespace LFMF {

/*******************************************************************************
 * Finds the roots to the equation @f$ Wi'(ti) - q*Wi(ti) = 0 @f$
 *
 * The parameter `i` selects the @f$i@f$-th root of the equation. The function
 * @f$ Wi(ti) @f$ is the "Airy function of the third kind" as defined by Hufford
 * [1] and Wait. The root is found by iteration starting from a real root.
 *
 * @note Although roots that are found for @f$ w_1 @f$ (Wait) and
 * @f$ \mathrm{Wi}^{(2)} @f$ (Hufford) will be equal, and the roots found for
 * @f$ w_2 @f$ (Wait) and @f$ \mathrm{Wi}^{(1)} @f$ (Hufford) will be equal, the
 * return values for `Wi` and `DWi` will not be the same. The input parameters for
 * kind and scale are used here as they are in `Airy()` for consistency.
 *
 * @param[in]  i        The @f$ i @f$-th complex root of
 *                      @f$ Wi'^{(2)}(ti) - q*Wi^{(2)}(ti) @f$, starting with 1.
 * @param[in]  q        Intermediate value: @f$ -j \nu \delta @f$
 * @param[in]  kind     Kind of Airy function to use, either `WONE` or `WTWO`
 * @param[in]  scaling  Type of scaling to use, either `HUFFORD` or `WAIT`
 * @param[out] DWi      Derivative of "Airy function of the third kind"
 *                      @f$ Wi'^{(2)}(ti) @f$
 * @param[out] Wi       "Airy function of the third kind" @f$ Wi^{(2)}(ti) @f$
 * @return              The @f$ i @f$-th complex root of the "Airy function of
 *                      the third kind"
 * 
 * @throws std::invalid_argument  If the values provided for `i`, `kind`, or
 *                                `scaling` are not valid for this function.
 * @throws std::runtime_error     If the root finding algorithm fails to converge.
 * 
 * **References**
 *     - "Airy Functions of the third kind" are found in equation 38 of [NTIA
 *       Report 87-219](https://its.ntia.gov/publications/details?pub=2242)
 *       "A General Theory of Radio Propagation through a Stratified Atmosphere",
 *       George Hufford, July 1987.
 * 
 * @see ITS::Propagation::LFMF::AiryKind
 * @see ITS::Propagation::LFMF::AiryScaling
 * @see ITS::Propagation::LFMF::Airy
 ******************************************************************************/
std::complex<double> WiRoot(
    const int i,
    std::complex<double> &DWi,
    const std::complex<double> q,
    std::complex<double> &Wi,
    const AiryKind kind,
    const AiryScaling scaling
) {
    std::complex<double> ph;  // Airy root phase
    std::complex<double> ti;  // ith cplx root of Wi'(2)(ti) - q*Wi(2)(ti) = 0
    std::complex<double> tw;  // Return variable

    std::complex<double> A;  // Temp
    double t, tt;            // Temp
    double eps;              // Temp
    int cnt;                 // Temp
    AiryKind dkind;          // Temp

    // From the NIST DLMF (Digital Library of Mathematical Functions)
    // http://dlmf.nist.gov/
    // The first 10 roots of Ai(Z) and Ai'(Z) can be found in: Table 9.9.1: Zeros of Ai and Ai.
    // Note: That ak is the root of Ai(ak) while akp (ak') is the root of Ai'(akp)

    // Root of the Airy function, Ai(ak)
    // TZERO(I) in GWINT.FOR
    constexpr double akp[11]
        = {-1.0187929716,
           -3.2481975822,
           -4.8200992112,
           -6.1633073556,
           -7.3721772550,
           -8.4884867340,
           -9.5354490524,
           -10.5276603970,
           -11.4750666335,
           -12.3847883718,
           -13.2636395229};

    // Root of the derivative of Airy function, Ai'(akp)
    // TINFIN(I) in GWINT.FOR
    constexpr double ak[11]
        = {-2.3381074105,
           -4.0879494441,
           -5.5205698281,
           -6.7867080901,
           -7.9441335871,
           -9.0226508533,
           -10.0401743416,
           -11.0085243037,
           -11.9360255632,
           -12.8287867529,
           -13.6914890352};

    // Verify that the input data is correct
    // Make sure that the desired root is greater than or equal to one
    if (i <= 0) {
        // Input `i` must be > 0; throw an exception
        std::ostringstream oss;
        oss << "WiRoot(): The root `i` must be > 0, not " << i;
        throw std::invalid_argument(oss.str());
    };

    if ((scaling != AiryScaling::HUFFORD) && (scaling != AiryScaling::WAIT)) {
        // Input `scaling` is invalid; throw an exception
        std::ostringstream oss;
        oss << "WiRoot(): `scaling` must be one of `HUFFORD` ("
            << static_cast<int>(AiryScaling::HUFFORD) << ") or `WAIT` ("
            << static_cast<int>(AiryScaling::WAIT) << "), not "
            << static_cast<int>(scaling);
        throw std::invalid_argument(oss.str());
    };

    if ((kind != AiryKind::WTWO) && (kind != AiryKind::WONE)) {
        // Input `kind` is invalid; throw an exception
        std::ostringstream oss;
        oss << "WiRoot(): `kind` must be one of `WTWO` ("
            << static_cast<int>(AiryKind::WTWO) << ") or `WONE` ("
            << static_cast<int>(AiryKind::WONE) << "), not "
            << static_cast<int>(kind);
        throw std::invalid_argument(oss.str());
    };
    // Input parameters verified

    // Initialize the Wi and Wi'(z)functions
    DWi = std::complex<double>(0.0, 0.0);  // Wi'(z)
    Wi = std::complex<double>(0.0, 0.0);   // Wi(z)

    // This routine starts with a real root of the Airy function to find the complex root
    // The real root has to be turned into a complex number.

    // ph is a factor that is used to find the root of the Wi function
    // Determine what scaling the user wants and which Wi function is used to set ph and
    // the dkind flag. This will allow that the real root that starts this process can be
    // scaled appropriately.
    // This is the similar to the initial scaling that is done in Airy()
    // Note that W1 Wait = Wi(2) Hufford and W2 Wait = Wi(1) Hufford
    // So the following inequalities keep this all straight
    if ((kind == AiryKind::WONE && scaling == AiryScaling::HUFFORD)
        || (kind == AiryKind::WTWO && scaling == AiryScaling::WAIT)) {
        // Wi(1)(Z) in Eqn 38 Hufford NTIA Report 87-219 or Wait W2
        ph = std::complex<double>(
            std::cos(-2.0 * PI / 3.0), std::sin(-2.0 * PI / 3.0)
        );
        // Set the dkind flag
        if (scaling == AiryScaling::WAIT) {
            dkind = AiryKind::DWTWO;
        } else {
            dkind = AiryKind::DWONE;
        };
    } else if ((kind == AiryKind::WTWO && scaling == AiryScaling::HUFFORD)
               || (kind == AiryKind::WONE && scaling == AiryScaling::WAIT)) {
        // Wi(2)(Z) in Eqn 38 Hufford NTIA Report 87-219 or Wait W1
        ph = std::complex<double>(
            std::cos(2.0 * PI / 3.0), std::sin(2.0 * PI / 3.0)
        );
        if (scaling == AiryScaling::WAIT) {
            dkind = AiryKind::DWONE;
        } else {
            dkind = AiryKind::DWTWO;
        };
    } else {
        dkind = AiryKind::DWONE;  // Not used, initialized for compile warning
    }

    // Note: The zeros of the Airy functions i[ak'] and Ak'[ak], ak' and ak, are on the negative real axis.
    // This is why 4*i+3 and 4*i+1 are used here instead of 4*k-3 and 4*k-1 which are
    // used in 9.9.8 and 9.9.6 in NIST DLMF. We are finding the ith negative root here.
    if (std::pow(std::abs(q), 3.0) <= 4 * (i - 1) + 3) {
        // Small Z, use ak' as the first guess (Ak(ak') = 0)
        if (i <= 10) {
            // The desired root is less than 10 so it is in the array above
            tt = akp[i - 1];
        } else {
            // The desired root is a higher order than those given in the ak array above
            // so we will approximate it from the first three terms of NIST DLMF 9.9.1.9
            // First find the argument (9.9.8) used in 9.9.1.9 for the ith negative root of Ai'(ak).
            t = (3.0 / 8.0) * PI * (4.0 * (i - 1) + 1);
            tt = -1.0 * std::pow(t, 2.0 / 3.0)
               * (1.0 - ((7.0 / 48.0) * std::pow(t, -2.0))
                  + ((35.0 / 288.0) * std::pow(t, -4.0)));
        };
        // Make the real Airy root complex
        ti = tt * ph;
        // t is now the solution for q = 0, The next step is the first Newton iteration
        ti = ti + q / ti;
    } else {
        // Large q, use ak as the first guess (Ai'(ak) = 0)
        if (i <= 10) {
            // The desired root is less than 10 so it is in the array above
            tt = ak[i - 1];
        } else {
            // The desired root must be approximated from the first three terms of NIST DLMF 9.9.1.8
            // First find the argument (9.9.6) used in 9.9.1.8 for the ith negative root of Ai(ak).
            t = (3.0 / 8.0) * PI * (4.0 * (i - 1) + 3.0);
            tt = -1.0 * std::pow(t, 2.0 / 3.0)
               * (1.0 + ((5.0 / 48.0) * std::pow(t, -2.0))
                  - ((5.0 / 36.0) * std::pow(t, -4.0)));
        };
        ti = tt * ph;
        // t is now the solution for Z = infinity. Next step the first newton iteration
        ti = ti + 1.0 / q;
    };

    cnt = 0;       // Set the iteration counter
    eps = 0.5e-6;  // Set the error desired for the iteration

    // Now iterate by Newton's method

    //////////////////////////////////////////////////////////////////////
    // Note: We can use the following from
    // Berry and Christman "The Path Integrals of LF/VLF Wave Hop Theory"
    // Radio Science Vol. 69D, No. 11 , November 1965
    // Eqn (14) E(t)  = W2'(t) - q W2(t)
    // Eqn (39) E'(t) = t W2(t) - q W2'(t)
    //////////////////////////////////////////////////////////////////////
    do {
        // f(q) = Wi'(ti) - q*Wi(ti)
        Wi = Airy(ti, kind, scaling);
        // f'(q) = tw*Wi(ti) - q*Wi'(ti);
        DWi = Airy(ti, dkind, scaling);
        // The Newton correction factor for iteration f(q)/f'(q)
        A = (DWi - q * (Wi)) / (ti * (Wi)-q * (DWi));
        ti = ti - A;  // New root guess ti
        cnt++;        // Increment the counter

    } while ((cnt <= 25)
             && ((std::abs((A / ti).real()) + (std::abs((A / ti).imag())) > eps)
             ));

    // Check to see if there if the loop converged on an answer
    // The cnt that fails is an arbitrary number; most converge in ~5 tries
    if (cnt == 26) {
        std::ostringstream oss;
        oss << "WiRoot(): Root finding algorithm did not converge after 25 "
               "iterations using Newton's method. Exiting.";
        throw std::runtime_error(oss.str());
    } else {
        // Converged!
        tw = ti;
    };

    return tw;
}

}  // namespace LFMF
}  // namespace Propagation
}  // namespace ITS