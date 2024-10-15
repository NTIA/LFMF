/** @file Utils.cpp
 * Implements various model-agnostic utility functions for the driver
 */
#include "Driver.h"

/*******************************************************************************
 * Print version information to the terminal
 ******************************************************************************/
void Version() {
    std::cout << std::setfill('*') << std::setw(55) << "" << std::endl;
    std::cout << "Institute for Telecommunications Sciences - Boulder, CO"
              << std::endl;
    std::cout << "\tDriver Version: " << DRIVER_VERSION << std::endl;
    std::cout << "\t" << LIBRARY_NAME << " Version: " << LIBRARY_VERSION
              << std::endl;
    std::cout << "Time: " << GetDatetimeString() << std::endl;
    std::cout << std::setfill('*') << std::setw(55) << "" << std::endl;
}

/*******************************************************************************
 * Helper function to format and print error messages encountered during
 * validation of input parameters
 * 
 * @param[in] opt  Command flag in error
 * @param[in] err  Error code
 * @return         Return code
 ******************************************************************************/
int Validate_RequiredErrMsgHelper(const char *opt, int err) {
    std::cerr << "Driver Error " << err << ": Option " << opt
              << " is required but was not provided" << std::endl;
    return err;
}

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
    struct std::tm localTime;

#ifdef _WIN32
    localtime_s(&localTime, &now);
#else
    if (localtime_r(&now, &localTime) == nullptr) {
        return "Date and time unknown";
    }
#endif
    char mbstr[100];
    if (std::strftime(mbstr, sizeof(mbstr), "%c", &localTime) == 0) {
        return "Could not format datetime string";
    }
    return std::string(mbstr);
}