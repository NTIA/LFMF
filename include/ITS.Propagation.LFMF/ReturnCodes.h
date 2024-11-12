/** @file ReturnCodes.h
 * Contains return codes used by this software
 */
#ifndef __ITS_PROPAGATION_LFMF_RETURNS_H__
#define __ITS_PROPAGATION_LFMF_RETURNS_H__

namespace ITS {
namespace Propagation {
namespace LFMF {

/*******************************************************************************
 * Return Codes defined by this software (0-127)
 ******************************************************************************/
// clang-format off
enum ReturnCode {
    SUCCESS = 0,                        ///< Return Success

    ERROR__TX_TERMINAL_HEIGHT = 32,		///< TX terminal height is out of range
    ERROR__RX_TERMINAL_HEIGHT,			///< RX terminal height is out of range
    ERROR__FREQUENCY,				    ///< Frequency is out of range
    ERROR__TX_POWER,					///< Transmit power is out of range
    ERROR__SURFACE_REFRACTIVITY,		///< Surface refractivity is out of range
    ERROR__PATH_DISTANCE,				///< Path distance is out of range
    ERROR__EPSILON,					    ///< Epsilon is out of range
    ERROR__SIGMA,					    ///< Sigma is out of range
    ERROR__POLARIZATION,				///< Invalid value for polarization
};
// clang-format on

}  // namespace LFMF
}  // namespace Propagation
}  // namespace ITS

#endif