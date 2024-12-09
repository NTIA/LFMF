/** @file LFMF.h
 * Interface header for this library
 */
#ifndef __ITS_PROPAGATION_LFMF_LFMF_H__
#define __ITS_PROPAGATION_LFMF_LFMF_H__

#include <complex>
#include <cfloat>           ///< for DBL_EPSILON

#include "LFMFConfig.h"

using std::complex;
using std::abs;

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

#define MAX(x, y) (((x) > (y)) ? (x) : (y))         ///< A macro that returns the maximum of \a a and \a b.
#define MIN(x, y) (((x) < (y)) ? (x) : (y))         ///< A macro that returns the minimum of \a a and \a b.
#define DIM(x, y) (((x) > (y)) ? (x - y) : (0))     ///< A macro that returns the difference of \a a and \a b.

constexpr double PI = 3.1415926535897932384;        ///< Approximate value of @f$ \pi @f$
constexpr double epsilon_0 = 8.854187817e-12;       ///< Vacuum permittivity (F/m)
constexpr double a_0__km = 6370;                    ///< Earth radius, in km
constexpr double C = 299792458.0;                   ///< Speed of light (m/s)
constexpr double THIRD = 1.0 / 3.0;                 ///< Value of one third
constexpr double D2R = PI / 180.0;                  ///< Approximate convert ratio from Degrees to Radians
constexpr double R2D = 180.0 / PI;                  ///< Approximate convert ratio from Radians to Degrees
constexpr double ETA = 119.9169832 * PI;            ///< Intrinsic impedance of free space (ohms)

constexpr int YES = 1;                              ///< Find the derivative i.e., Ai'() or Bi'()
constexpr int NO = 0;                               ///< Find Ai() or Bi()

/*******************************************************************************
 * Polarization
 ******************************************************************************/
// clang-format off
enum Polarization {
    POLARIZATION__HORIZONTAL,           ///< Polarization horizontal
    POLARIZATION__VERTICAL,             ///< Polarization vertical
};
// clang-format on

/*******************************************************************************
 * Solution method
 ******************************************************************************/
// clang-format off
enum SolutionMethod {
    METHOD__FLAT_EARTH_CURVE,           ///< Flat earth curve method
    METHOD__RESIDUE_SERIES,             ///< Residue series method
};
// clang-format on

/*******************************************************************************
 * Airy function kind
 ******************************************************************************/
// clang-format off
enum AiryFunctionKind {
    AIRY = 1,                           ///< Find the Airy Function 
    AIRYD,                              ///< Find the Airy function Derivative
    BAIRY,                              ///< Find the Bairy Function
    BAIRYD,                             ///< Find the Bairy function Derivative
    WTWO,                               ///< find Hufford Wi(2) or Wait W2
    DWTWO,                              ///< find Hufford Wi'(2) or Wait W2'
    WONE,                               ///< find Hufford Wi(1) or Wait W1
    DWONE,                              ///< find Hufford Wi'(1) or Wait W1'
};
// clang-format on

/*******************************************************************************
 * Airy function scaling
 ******************************************************************************/
// clang-format off
enum AiryFunctionScaling {
    HUFFORD,                            ///< Use Hufford scaling
    WAIT,                               ///< Use Wait scaling
    NONE,                               ///< No Scaling
};
// clang-format on

/*******************************************************************************
 * Return Codes defined by this software (0-127)
 ******************************************************************************/
// clang-format off
enum ReturnCode {
    SUCCESS = 0,                        ///< Return Success

    // Invalid Inputs
    ERROR__TX_TERMINAL_HEIGHT = 32,     ///< TX terminal height is out of range
    ERROR__RX_TERMINAL_HEIGHT,          ///< RX terminal height is out of range
    ERROR__FREQUENCY,                   ///< Frequency is out of range
    ERROR__TX_POWER,                    ///< Transmit power is out of range
    ERROR__SURFACE_REFRACTIVITY,        ///< Surface refractivity is out of range
    ERROR__PATH_DISTANCE,               ///< Path distance is out of range
    ERROR__EPSILON,                     ///< Epsilon is out of range
    ERROR__SIGMA,                       ///< Sigma is out of range
    ERROR__POLARIZATION,                ///< Invalid value for polarization
};
// clang-format on

//////////////////////////////////////
// Data Structures

/** @struct Result
 * struct Result for outputs
 */
struct Result
{
    double A_btl__db;               ///< Basic transmission loss, in dB
    double E_dBuVm;                 ///< Electrice field strength, in dB(uV/m)
    double P_rx__dbm;               ///< Received power, in dBm

    SolutionMethod method;          ///< Solution method: 0 = Flat earth with curve correction, 1 = Residue series
};

//////////////////////////////////////
// Public Functions

DLLEXPORT ReturnCode LFMF(double h_tx__meter, double h_rx__meter, double f__mhz, double P_tx__watt, double N_s,
    double d__km, double epsilon, double sigma, int pol, Result *result);

DLLEXPORT char *GetReturnStatusCharArray(const int code);
DLLEXPORT void FreeReturnStatusCharArray(char *c_msg);

//////////////////////////////////////
// Private Functions

ReturnCode LFMF_CPP(double h_tx__meter, double h_rx__meter, double f__mhz, double P_tx__watt, double N_s,
    double d__km, double epsilon, double sigma, Polarization pol, Result *result);
std::string GetReturnStatus(const int code);
double FlatEarthCurveCorrection(complex<double> delta, complex<double> q, double h_1__km, double h_2__km, double d, double k, double a_e__km);
double ResidueSeries(double k, double h_1__km, double h_2__km, double nu, double theta, complex<double> q);
complex<double> wofz(complex<double> qi);
complex<double> Airy(complex<double> Z, AiryFunctionKind kind, AiryFunctionScaling scaling);
complex<double> WiRoot(int i, complex<double> *DWi, complex<double> q, complex<double> *Wi,
    AiryFunctionKind kind, AiryFunctionScaling scaling);
ReturnCode ValidateInput(double h_tx__meter, double h_rx__meter, double f__mhz, double P_tx__watt,
    double N_s, double d__km, double epsilon, double sigma);
ReturnCode ValidatePolarization(int pol);
bool AlmostEqualRelative(double A, double B, double maxRelDiff = DBL_EPSILON);

}  // namespace LFMF
}  // namespace Propagation
}  // namespace ITS

#endif