/** @file Errors.h
 * Defines return codes for the driver
 */
#ifndef __DRIVER_ERRORS_H__
#define __DRIVER_ERRORS_H__

// Define "SUCCESS" macro if not imported already
#ifndef SUCCESS
#define SUCCESS 0 /**< Successful execution */
#endif

// Primary Return Codes
#define DRVR__RETURN_SUCCESS                9000  /**< Internal driver success code */
#define DRVRERR__MISSING_OPTION             9001  /**< No value provided for given argument */
#define DRVRERR__INVALID_OPTION             9002  /**< Unknown option specified */
#define DRVRERR__OPENING_INPUT_FILE         9003  /**< Failed to open the input file for reading */
#define DRVRERR__OPENING_OUTPUT_FILE        9004  /**< Failed to open the output file for writing */

// Input File Parsing Errors
#define DRVRERR__PARSE                      9100  /**< General error parsing inputs */

// Validation Errors
#define DRVRERR__VALIDATION_IN_FILE         9200  /**< Input file not specified */
#define DRVRERR__VALIDATION_OUT_FILE        9201  /**< Output file not specified */

#endif