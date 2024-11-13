/** @file ReturnCodes.h
 * Defines return codes for the driver
 */
#ifndef __LFMF_DRIVER_RETURNS_H__
#define __LFMF_DRIVER_RETURNS_H__

/*******************************************************************************
 * Return Codes defined by this driver software (128-255)
 ******************************************************************************/
// clang-format off
enum DrvrReturnCode {
    // Primary Return Codes
    DRVR__SUCCESS = 128,                    /**< Successful execution */
    DRVR__RETURN_SUCCESS,                   /**< Indicates driver should exit successfully */
    DRVRERR__MISSING_OPTION,                /**< No value provided for given argument */
    DRVRERR__INVALID_OPTION,                /**< Unknown option specified */
    DRVRERR__OPENING_INPUT_FILE,            /**< Failed to open the input file for reading */
    DRVRERR__OPENING_OUTPUT_FILE,           /**< Failed to open the output file for writing */

    // Input File Parsing Errors
    DRVRERR__PARSE = 160,                   /**< Failed parsing inputs; unknown parameter */
    DRVRERR__PARSE_TX_TERMINAL_HEIGHT,      /**< Failed to parse TX terminal height value */
    DRVRERR__PARSE_RX_TERMINAL_HEIGHT,      /**< Failed to parse RX terminal height value */
    DRVRERR__PARSE_FREQUENCY,               /**< Failed to parse frequency value */
    DRVRERR__PARSE_TX_POWER,                /**< Failed to parse transmit power value */
    DRVRERR__PARSE_SURFACE_REFRACTIVITY,    /**< Failed to parse surface refractivity value */
    DRVRERR__PARSE_PATH_DISTANCE,           /**< Failed to parse path distance value */
    DRVRERR__PARSE_EPSILON,                 /**< Failed to parse epsilon value */
    DRVRERR__PARSE_SIGMA,                   /**< Failed to parse sigma value */
    DRVRERR__PARSE_POLARIZATION,            /**< Failed to parse polarization value */

    // Validation Errors
    DRVRERR__VALIDATION_IN_FILE = 192,      /**< Input file not specified */
    DRVRERR__VALIDATION_OUT_FILE,           /**< Output file not specified */
};
// clang-format on

std::string GetDrvrReturnStatus(int code);

#endif