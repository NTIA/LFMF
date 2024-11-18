/** @file LFMF.h
 * Interface header for this library
 */
#ifndef __ITS_PROPAGATION_LFMF_LFMF_H__
#define __ITS_PROPAGATION_LFMF_LFMF_H__

#include <complex>

#include "LFMFConfig.h"
#include "ReturnCodes.h"

using std::complex;

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

#define MAX(x, y) (((x) > (y)) ? (x) : (y))                 ///< A macro that returns the maximum of \a a and \a b.
#define MIN(x, y) (((x) < (y)) ? (x) : (y))                 ///< A macro that returns the minimum of \a a and \a b.
#define DIM(x, y) (((x) > (y)) ? (x - y) : (0))             ///< A macro that returns the difference of \a a and \a b.

#define PI                          3.1415926535897932384   ///< Approximate value of @f$ \pi @f$
#define epsilon_0                   8.854187817e-12         ///< Vacuum permittivity (F/m) 
#define a_0__km                     6370                    ///< Earth radius, in km
#define C                           299792458.0             ///< Speed of light (m/s)
#define SQRTPI                      sqrt(PI)                ///< Approximate value of the square root of @f$ \pi @f$
#define THIRD                       1.0 / 3.0               ///< Value of one third 
#define FALSE                       0                       ///< False
#define TRUE                        1                       ///< True
#define D2R                         PI/180.0                ///< Approximate convert ratio from Degrees to Radians
#define R2D                         180.0/PI                ///< Approximate convert ratio from Radians to Degrees
#define ETA                         119.9169832*PI          ///< Intrinsic impedance of free space (ohms)

#define POLARIZATION__HORIZONTAL    0                       ///< Polarization horizontal
#define POLARIZATION__VERTICAL      1                       ///< Polarization vertical

#define METHOD__FLAT_EARTH_CURVE    0                       ///< Flat earth curve method
#define METHOD__RESIDUE_SERIES      1                       ///< Residue series method

#define YES                         1                       ///< Find the derivative i.e., Ai'() or Bi'()
#define NO                          0                       ///< Find Ai() or Bi()
// kind
#define AIRY                        1                       ///< Find the Airy Function 
#define AIRYD                       2                       ///< Find the Airy function Derivative
#define BAIRY                       3                       ///< Find the Bairy Function
#define BAIRYD                      4                       ///< Find the Bairy function Derivative
#define WTWO                        5                       ///< find Hufford Wi(2) or Wait W2
#define DWTWO                       6                       ///< find Hufford Wi'(2) or Wait W2'
#define WONE                        7                       ///< find Hufford Wi(1) or Wait W1
#define DWONE                       8                       ///< find Hufford Wi'(1) or Wait W1'
// scaling
#define HUFFORD                     9                       ///< Use Hufford scaling
#define WAIT                        10                      ///< Use Wait scaling
#define NONE                        11                      ///< No Scaling

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

    int method;                     ///< Solution method: 0 = Flat earth with curve correction, 1 = Residue series
};

//////////////////////////////////////
// Public Functions

DLLEXPORT ReturnCode LFMF(double h_tx__meter, double h_rx__meter, double f__mhz, double P_tx__watt,
    double N_s, double d__km, double epsilon, double sigma, int pol, Result *result);

DLLEXPORT char *GetReturnStatusCharArray(const int code);
DLLEXPORT void FreeReturnStatusCharArray(char *c_msg);

//////////////////////////////////////
// Private Functions

std::string GetReturnStatus(const int code);
double FlatEarthCurveCorrection(complex<double> delta, complex<double> q, double h_1__km, double h_2__km, double d, double k, double a_e__km);
double ResidueSeries(double d, double k, double h_1__km, double h_2__km, double nu, double theta, complex<double> q);
complex<double> wofz(complex<double> qi);
complex<double> Airy(complex<double> Z, int kind, int scaling);
complex<double> WiRoot(int i, complex<double> *DWi, complex<double> q, complex<double> *Wi, int kind, int scaling);
ReturnCode ValidateInput(double h_tx__meter, double h_rx__meter, double f__mhz, double P_tx__watt,
    double N_s, double d__km, double epsilon, double sigma, int pol);

}  // namespace LFMF
}  // namespace Propagation
}  // namespace ITS

#endif