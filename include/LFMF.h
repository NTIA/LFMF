/** @file LFMF.h
 * Interface header for this library
 */
#pragma once

#include <cfloat>   // for DBL_EPSILON
#include <complex>  // for std::complex
#include <string>   // for std::string

namespace ITS {
namespace Propagation {
namespace LFMF {

// Define cross-platform DLLEXPORT
// Export the DLL functions as "C" and not C++
#ifndef DOXYGEN_SHOULD_SKIP
    #ifdef _WIN32
        #define DLLEXPORT extern "C" __declspec(dllexport)
    #else
        #define DLLEXPORT extern "C"
    #endif
#endif

////////////////////////////////////////////////////////////////////////////////
// Enums

/** Valid RF polarizations for use of this model */
enum Polarization {
    HORIZONTAL = 0, /**< Horizontal polarization */
    VERTICAL = 1,   /**< Vertical polarization */
};

/** Solution method used to generate model result */
enum SolutionMethod {
    FLAT_EARTH_CURVE, /**< Flat earth curve method */
    RESIDUE_SERIES,   /**< Residue series method */
};

/*******************************************************************************
 * Kinds of Airy functions to specify for `Airy()` and `WiRoot()` operation.
 * 
 * The members of this enum allow specification of Airy functions of the first
 * (`AIRY`), second (`BAIRY`), or third (`WONE` and `WTWO`) kind. These Airy
 * functions of a third kind are specified by Hufford in NTIA Report 87-219. The
 * enum also allows selection of derivatives of any of these functions.
 * 
 * @note Hufford's Airy functions of a third kind @f$ \mathrm{Wi}^{(1)} @f$
 * and @f$ \mathrm{Wi}^{(2)} @f$ are, aside from a multiplicative constant,
 * the same as Wait's @f$ w_2 @f$ and @f$ w_1 @f$.
 * @see ITS::Propagation::LFMF::Airy
 * @see ITS::Propagation::LFMF::WiRoot
 * @see ITS::Propagation::LFMF::AiryFunctionScaling
 ******************************************************************************/
// clang-format off
enum AiryFunctionKind {
    AIRY = 1, /**< Airy function of the first kind, @f$ \mathrm{Ai}(x) @f$ */
    AIRYD,    /**< Derivative of `AIRY`, @f$ \mathrm{Ai}'(x) @f$ */
    BAIRY,    /**< Airy function of the second kind, @f$ \mathrm{Bi}(x) @f$ */
    BAIRYD,   /**< Derivative of `BAIRY`, @f$ \mathrm{Bi}'(x) @f$ */
    WTWO,     /**< Hufford's Airy function of a third kind, @f$ \mathrm{Wi}^{(2)} @f$ (Wait's @f$ w_1 @f$) */
    DWTWO,    /**< Derivative of `WTWO`, @f$ \mathrm{Wi}'^{(2)} @f$ (Wait's @f$ w_1' @f$) */
    WONE,     /**< Hufford's Airy function of a third kind, @f$ \mathrm{Wi}'^{(1)} @f$ (Wait's @f$ w_2 @f$)*/
    DWONE,    /**< Derivative of `WONE`, @f$ \mathrm{Wi}'^{(1)} @f$ (Wait's @f$ w_2' @f$) */
};
// clang-format on

/*******************************************************************************
 * Multiplicative scaling to use when dealing with Airy functions.
 * 
 * The differences in these scaling options are discussed at length in the
 * documentation for ITS::Propagation::LFMF::Airy.
 * 
 * @see ITS::Propagation::LFMF::Airy
 * @see ITS::Propagation::LFMF::WiRoot
 * @see ITS::Propagation::LFMF::AiryFunctionKind
 ******************************************************************************/
enum AiryFunctionScaling {
    HUFFORD, /**< Use Hufford scaling */
    WAIT,    /**< Use Wait scaling */
    NONE,    /**< No Scaling */
};

/*******************************************************************************
 * Return Codes defined by this software (0-127)
 ******************************************************************************/
// clang-format off
enum ReturnCode {
    SUCCESS = 0,                        /**< Return Success */

    // Invalid Inputs
    ERROR__TX_TERMINAL_HEIGHT = 32,     /**< TX terminal height is out of range */
    ERROR__RX_TERMINAL_HEIGHT,          /**< RX terminal height is out of range */
    ERROR__FREQUENCY,                   /**< Frequency is out of range */
    ERROR__TX_POWER,                    /**< Transmit power is out of range */
    ERROR__SURFACE_REFRACTIVITY,        /**< Surface refractivity is out of range */
    ERROR__PATH_DISTANCE,               /**< Path distance is out of range */
    ERROR__EPSILON,                     /**< Epsilon is out of range */
    ERROR__SIGMA,                       /**< Sigma is out of range */
    ERROR__POLARIZATION,                /**< Invalid value for polarization */
};
// clang-format on

////////////////////////////////////////////////////////////////////////////////
// Constants
// clang-format off
constexpr double PI = 3.1415926535897932384;   /**< Approximate value of @f$ \pi @f$ */
constexpr double epsilon_0 = 8.854187817e-12;  /**< Vacuum permittivity (F/m) */
constexpr double a_0__km = 6370;               /**< Earth radius, in km */
constexpr double C = 299792458.0;              /**< Speed of light (m/s) */
constexpr double ETA = 119.9169832 * PI;       /**< Intrinsic impedance of free space (ohms) */
// clang-format on

////////////////////////////////////////////////////////////////////////////////
// Data Structures

/** Structure to hold LF/MF model outputs. */
struct Result {
        double A_btl__db;      /**< Basic transmission loss, in dB */
        double E_dBuVm;        /**< Electric field strength, in dB(uV/m) */
        double P_rx__dbm;      /**< Received power, in dBm */
        SolutionMethod method; /**< Method used to obtain results */
};

////////////////////////////////////////////////////////////////////////////////
// Public Functions

DLLEXPORT ReturnCode LFMF(
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
);

DLLEXPORT char *GetReturnStatusCharArray(const int code);
DLLEXPORT void FreeReturnStatusCharArray(char *c_msg);

////////////////////////////////////////////////////////////////////////////////
// Private Functions

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
);
std::string GetReturnStatus(const int code);
double FlatEarthCurveCorrection(
    const std::complex<double> delta,
    const std::complex<double> q,
    const double h_1__km,
    const double h_2__km,
    const double d,
    const double k,
    const double a_e__km
);
double ResidueSeries(
    const double k,
    const double h_1__km,
    const double h_2__km,
    const double nu,
    const double theta,
    const std::complex<double> q
);
std::complex<double> wofz(const std::complex<double> z);
std::complex<double> Airy(
    const std::complex<double> Z,
    const AiryFunctionKind kind,
    const AiryFunctionScaling scaling
);
std::complex<double> WiRoot(
    const int i,
    std::complex<double> &DWi,
    const std::complex<double> q,
    std::complex<double> &Wi,
    const AiryFunctionKind kind,
    const AiryFunctionScaling scaling
);
ReturnCode ValidateInput(
    const double h_tx__meter,
    const double h_rx__meter,
    const double f__mhz,
    const double P_tx__watt,
    const double N_s,
    const double d__km,
    const double epsilon,
    const double sigma
);
ReturnCode ValidatePolarization(const int pol);
bool AlmostEqualRelative(
    const double A, const double B, const double maxRelDiff = DBL_EPSILON
);

}  // namespace LFMF
}  // namespace Propagation
}  // namespace ITS
