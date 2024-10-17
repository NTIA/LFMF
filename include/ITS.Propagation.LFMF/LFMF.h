/** @file LFMF.h
 * Interface header for this library
 */
#ifndef __ITS_PROPAGATION_LFMF_LFMF_H__
#define __ITS_PROPAGATION_LFMF_LFMF_H__

#include <complex>

namespace ITS {
namespace PROPAGATION {
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

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define DIM(x, y) (((x) > (y)) ? (x - y) : (0))

using std::complex;

#define PI                          3.1415926535897932384
#define epsilon_0                   8.854187817e-12         // Vacuum permittivity (F/m) 
#define a_0__km                     6370                    // Earth radius, in km
#define C                           299792458.0             // Speed of light (m/s)
#define SQRTPI                      sqrt(PI)
#define THIRD                       1.0 / 3.0
#define FALSE                       0
#define TRUE                        1
#define D2R                         PI/180.0
#define R2D                         180.0/PI
#define ETA                         119.9169832*PI          // Intrinsic impedance of free space (ohms)

#define POLARIZATION__HORIZONTAL    0
#define POLARIZATION__VERTICAL      1

#define METHOD__FLAT_EARTH_CURVE    0
#define METHOD__RESIDUE_SERIES      1

#define YES                         1   // Find the derivative i.e., Ai'() or Bi'()
#define NO                          0   // Find Ai() or Bi()
// kind
#define AIRY                        1   // Find the Airy Function 
#define AIRYD                       2   // Find the Airy function Derivative
#define BAIRY                       3   // Find the Bairy Function
#define BAIRYD                      4   // Find the Bairy function Derivative
#define WTWO                        5   // find Hufford Wi(2) or Wait W2
#define DWTWO                       6   // find Hufford Wi'(2) or Wait W2'
#define WONE                        7   // find Hufford Wi(1) or Wait W1
#define DWONE                       8   // find Hufford Wi'(1) or Wait W1'
// scaling
#define HUFFORD                     9   // Use Hufford scaling
#define WAIT                        10  // Use Wait scaling
#define NONE                        11  // No Scaling

// Return codes
#define SUCCESS                     0

// Error codes
#define ERROR__TX_TERMINAL_HEIGHT               1000    // TX terminal height is out of range
#define ERROR__RX_TERMINAL_HEIGHT               1001    // RX terminal height is out of range
#define ERROR__FREQUENCY                        1002    // Frequency is out of range
#define ERROR__TX_POWER                         1003    // Transmit power is out of range
#define ERROR__SURFACE_REFRACTIVITY             1004    // Surface refractivity is out of range
#define ERROR__PATH_DISTANCE                    1005    // Path distance is out of range
#define ERROR__EPSILON                          1006    // Epsilon is out of range
#define ERROR__SIGMA                            1007    // Sigma is out of range
#define ERROR__POLARIZATION                     1008    // Invalid value for polarization

//////////////////////////////////////
// Data Structures

struct Result
{
    double A_btl__db;
    double E_dBuVm;
    double P_rx__dbm;

    int method;
};

//////////////////////////////////////
// Main LFMF Function

DLLEXPORT int LFMF(double h_tx__meter, double h_rx__meter, double f__mhz, double P_tx__watt,
    double N_s, double d__km, double epsilon, double sigma, int pol, Result *result);

//////////////////////////////////////
// Helper Functions

double FlatEarthCurveCorrection(complex<double> delta, complex<double> q, double h_1__km, double h_2__km, double d, double k, double a_e__km);
double ResidueSeries(double d, double k, double h_1__km, double h_2__km, double nu, double theta, complex<double> q);
complex<double> wofz(complex<double> qi);
complex<double> Airy(complex<double> Z, int kind, int scaling);
complex<double> WiRoot(int i, complex<double> *DWi, complex<double> q, complex<double> *Wi, int kind, int scaling);
int ValidateInput(double h_tx__meter, double h_rx__meter, double f__mhz, double P_tx__watt,
    double N_s, double d__km, double epsilon, double sigma, int pol);

}  // namespace LFMF
}  // namespace PROPAGATION
}  // namespace ITS

#endif