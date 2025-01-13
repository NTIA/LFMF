/** @file ValidateInputs.cpp
 * Implements the model from ITS.Propagation.LFMF.
 */

#include "LFMF.h"

namespace ITS {
namespace Propagation {
namespace LFMF {

/*******************************************************************************
 * Validate that model input values are within valid ranges.
 *
 * @param[in] h_tx__meter  Height of the transmitter, in meters
 * @param[in] h_rx__meter  Height of the receiver, in meters
 * @param[in] f__mhz       Frequency, in MHz
 * @param[in] P_tx__watt   Transmitter power, in watts
 * @param[in] N_s          Surface refractivity, in N-Units
 * @param[in] d__km        Path distance, in km
 * @param[in] epsilon      Relative permittivity
 * @param[in] sigma        Conductivity, in siemens per meter
 * @return                 Return code
 ******************************************************************************/
ReturnCode ValidateInput(
    const double h_tx__meter,
    const double h_rx__meter,
    const double f__mhz,
    const double P_tx__watt,
    const double N_s,
    const double d__km,
    const double epsilon,
    const double sigma
) {
    if (h_tx__meter < 0 || h_tx__meter > 50)
        return ERROR__TX_TERMINAL_HEIGHT;

    if (h_rx__meter < 0 || h_rx__meter > 50)
        return ERROR__RX_TERMINAL_HEIGHT;

    if (f__mhz < 0.01 || f__mhz > 30)
        return ERROR__FREQUENCY;

    if (P_tx__watt <= 0)
        return ERROR__TX_POWER;

    if (N_s < 250 || N_s > 400)
        return ERROR__SURFACE_REFRACTIVITY;

    if (d__km < 0.001 || d__km > 10000)
        return ERROR__PATH_DISTANCE;

    if (epsilon < 1)
        return ERROR__EPSILON;

    if (sigma <= 0)
        return ERROR__SIGMA;

    return SUCCESS;
}


/******************************************************************************
 * Perform input Polarization validation
 *
 * @param[in] pol  Polarization
 * @return         Return code
 ******************************************************************************/
ReturnCode ValidatePolarization(const int pol) {
    if (pol != POLARIZATION__HORIZONTAL && pol != POLARIZATION__VERTICAL)
        return ERROR__POLARIZATION;
    return SUCCESS;
}

}  // namespace LFMF
}  // namespace Propagation
}  // namespace ITS