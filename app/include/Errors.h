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
#define     DRVR__RETURN_SUCCESS                    1000
#define     DRVRERR__INVALID_OPTION                 1003
#define     DRVRERR__OPENING_INPUT_FILE             1006
#define     DRVRERR__OPENING_OUTPUT_FILE            1007

/** Input File Parsing Errors (1100-1199) */
#define     DRVRERR__PARSE                          1100

// TODO-TEMPLATE: Add driver error codes and document them in app/README.md

/** Validation Errors (1200-1299) */
#define     DRVRERR__VALIDATION_IN_FILE             1202
#define     DRVRERR__VALIDATION_OUT_FILE            1203

// clang-format on