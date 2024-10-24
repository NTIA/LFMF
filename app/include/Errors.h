/** @file Errors.h
 * Defines return codes for the driver
 */
#pragma once

// TODO-TEMPLATE: If needed, include existing return codes defined by the library
// #include "<TODO-TEMPLATE>/Errors.h"

// clang-format off

// Define "SUCCESS" macro if not imported already
#ifndef SUCCESS
#define SUCCESS 0 /**< Successful execution */
#endif

/** Primary Return Codes (1000-1099) */
#define DRVR__RETURN_SUCCESS                1000  /**< Internal driver success code */
#define DRVRERR__MISSING_OPTION             1001  /**< No value provided for given argument */
#define DRVRERR__INVALID_OPTION             1002  /**< Unknown option specified */
#define DRVRERR__OPENING_INPUT_FILE         1003  /**< Failed to open the input file for reading */
#define DRVRERR__OPENING_OUTPUT_FILE        1004  /**< Failed to open the output file for writing */

/** Input File Parsing Errors (1100-1199) */
#define DRVRERR__PARSE                      1100  /**< General error parsing inputs */

// TODO-TEMPLATE: Add driver error codes and document them in app/README.md

/** Validation Errors (1200-1299) */
#define DRVRERR__VALIDATION_IN_FILE             1200  /**< Input file not specified */
#define DRVRERR__VALIDATION_OUT_FILE            1201  /**< Output file not specified */

// clang-format on