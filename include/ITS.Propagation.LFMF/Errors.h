/** @file LFMF.h
 * Interface header for this library
 */
#ifndef __ITS_PROPAGATION_LFMF_ERRORS_H__
#define __ITS_PROPAGATION_LFMF_ERRORS_H__

namespace ITS {
namespace Propagation {
namespace LFMF {

// Return codes
#define SUCCESS							0			///< Return Success

// Error codes
#define ERROR__TX_TERMINAL_HEIGHT		1000		///< TX terminal height is out of range
#define ERROR__RX_TERMINAL_HEIGHT		1001		///< RX terminal height is out of range
#define ERROR__FREQUENCY				1002        ///< Frequency is out of range
#define ERROR__TX_POWER					1003        ///< Transmit power is out of range
#define ERROR__SURFACE_REFRACTIVITY		1004        ///< Surface refractivity is out of range
#define ERROR__PATH_DISTANCE			1005		///< Path distance is out of range
#define ERROR__EPSILON					1006        ///< Epsilon is out of range
#define ERROR__SIGMA					1007        ///< Sigma is out of range
#define ERROR__POLARIZATION				1008		///< Invalid value for polarization

}  // namespace LFMF
}  // namespace Propagation
}  // namespace ITS

#endif