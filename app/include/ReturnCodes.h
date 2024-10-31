/** @file Errors.h
 * Defines return codes for the driver
 */
#pragma once

#include <string>  // for std::string

// TODO-TEMPLATE: Add driver return codes here and corresponding entries in app/src/ReturnCodes.cpp

/*******************************************************************************
 * Return Codes defined by this driver software.
 ******************************************************************************/
// clang-format off
enum DrvrReturnCode {
    // Primary Return Codes (1000-1099)
    DRVR__SUCCESS = 1000,                /**< Successful execution */
    DRVR__RETURN_SUCCESS,                /**< Indicates driver should exit successfully */
    DRVRERR__MISSING_OPTION,             /**< No value provided for given argument */
    DRVRERR__INVALID_OPTION,             /**< Unknown option specified */
    DRVRERR__OPENING_INPUT_FILE,         /**< Failed to open the input file for reading */
    DRVRERR__OPENING_OUTPUT_FILE,        /**< Failed to open the output file for writing */

    // Input File Parsing Errors (1100-1199)
    DRVRERR__PARSE = 1100,               /**< Failed parsing inputs; unknown parameter */

    // Validation Errors (1200-1299)
    DRVRERR__VALIDATION_IN_FILE = 1200,  /**< Input file not specified */
    DRVRERR__VALIDATION_OUT_FILE,        /**< Output file not specified */
};
// clang-format on

std::string GetDrvrReturnStatus(int code);
