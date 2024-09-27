/** @file Utils.cpp
 * Implements utility functions for parsing driver inputs from text
 */
#include "Driver.h"

/*******************************************************************************
 * Parse an integer value read from the input parameter file
 * 
 * @param[in]  str    Input file value as string
 * @param[out] value  Input file value converted to int
 * @return            Return code
 ******************************************************************************/
int ParseInteger(const char *str, int &value) {
    size_t t;

    try {
        value = std::stoi(str, &t, 10);
    } catch (...) {
        // error parsing the input string value
        return DRVRERR__PARSE;
    }

    // verify the entire string was parsed, and a trailing char wasn't omitted
    if (std::strlen(str) != t)
        return DRVRERR__PARSE;

    return SUCCESS;
}

/*******************************************************************************
 * Parse a double value read from the input parameter file
 * 
 * @param[in]  str    Input file value as string
 * @param[out] value  Input file value converted to double
 * @return            Return code
 ******************************************************************************/
int ParseDouble(const char *str, double &value) {
    try {
        value = std::stod(str);
    } catch (...) {
        // error parsing the input string value
        return DRVRERR__PARSE;
    }

    return SUCCESS;
}

/*******************************************************************************
 * Common error handling function
 * 
 * @param[in] err  Error parsing code
 * @param[in] msg  Error message
 * @return         Error code from input param
 ******************************************************************************/
int ParsingErrorHelper(int err, const char *msg) {
    std::cerr << "Driver Error " << err << ": Unable to parse '" << msg
              << "' value." << std::endl;
    return err;
}

/******************************************************************************
 * Get a string containing the current date and time information.
 * 
 * @return  A localized standard date and time string (locale dependent)
 ******************************************************************************/
std::string GetDatetimeString() {
    std::time_t now = std::time(nullptr);
    char mbstr[100];
    // Warning: std::localtime may or may not be thread-safe
    std::strftime(mbstr, sizeof(mbstr), "%c", std::localtime(&now));
    std::string dtString = mbstr;
    return dtString;
}