/** @file DriverUtils.cpp
 * Implements various model-agnostic utility functions for the driver
 */
#include "Driver.h"

#ifdef _WIN32
    // Ensure localtime_s is available on Windows
    #ifndef __STDC_LIB_EXT1__
        #define __STDC_LIB_EXT1__
    #endif
    #ifndef __STDC_WANT_LIB_EXT1__
        #define __STDC_WANT_LIB_EXT1__ 1
    #endif
#endif

#include <algorithm> // for std::transform
#include <cctype>    // for std::tolower
#include <ctime>     // for localtime_{s,r}, std::{time, time_t, tm, strftime}
#include <fstream>   // for std::ofstream
#include <iomanip>   // for std::setfill, std::setw
#include <iostream>  // for std::cerr, std::endl
#include <string>    // for std::stod, std::stoi, std::string

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

/*******************************************************************************
 * Parse a double value read from the input parameter file
 * 
 * @param[in]  str    Input file value as string
 * @param[out] value  Input file value converted to double
 * @return            Return code
 ******************************************************************************/
int ParseDouble(const std::string &str, double &value) {
    try {
        value = std::stod(str);
    } catch (...) {
        // error parsing the input string value
        return DRVRERR__PARSE;
    }

    return SUCCESS;
}

/*******************************************************************************
 * Parse an integer value read from the input parameter file
 * 
 * @param[in]  str    Input file value as string
 * @param[out] value  Input file value converted to int
 * @return            Return code
 ******************************************************************************/
int ParseInteger(const std::string &str, int &value) {
    try {
        size_t pos;
        value = std::stoi(str, &pos, 10);

        // Verify the entire string was parsed
        if (pos != str.size()) {
            return DRVRERR__PARSE;
        }
    } catch (...) {
        // error parsing the input string value
        return DRVRERR__PARSE;
    };

    return SUCCESS;
}

/*******************************************************************************
 * Common error handling function
 * 
 * @param[in] err  Error parsing code
 * @param[in] msg  Error message
 * @return         Error code from input param
 ******************************************************************************/
int ParsingErrorHelper(const int err, const std::string &msg) {
    std::cerr << "Driver Error " << err << ": Unable to parse '" << msg
              << "' value." << std::endl;
    return err;
}

/*******************************************************************************
 * Helper function to standardize printing of text labels to file
 * 
 * @param[in] fp   Output stream, a text file open for writing
 * @param[in] lbl  Text message
 ******************************************************************************/
void PrintLabel(std::ofstream &fp, const std::string &lbl) {
    fp << "[" << lbl << "]";
}


/******************************************************************************
 * Convert a string to lowercase.
 * 
 * @param[in, out] str  The string to convert
 ******************************************************************************/
void StringToLower(std::string &str) {
    std::transform(str.begin(), str.end(), str.begin(), [](const char c) {
        return static_cast<char>(std::tolower(c));
    });
}

/*******************************************************************************
 * Helper function to format and print error messages encountered during
 * validation of input parameters
 * 
 * @param[in] opt  Command flag in error
 * @param[in] err  Error code
 * @return         Return code
 ******************************************************************************/
int Validate_RequiredErrMsgHelper(const std::string &opt, const int err) {
    std::cerr << "Driver Error " << err << ": Option \"" << opt
              << "\" is required but was not provided" << std::endl;
    return err;
}

/*******************************************************************************
 * Print version information to the specified output stream 
 * 
 * @param[in] os  Output stream for writing; defaults to `std::cout`
 ******************************************************************************/
void Version(std::ostream &os) {
    os << std::setfill('*') << std::setw(55) << "" << std::endl;
    os << "Institute for Telecommunication Sciences - Boulder, CO" << std::endl;
    os << "\tDriver Version: " << DRIVER_VERSION << std::endl;
    os << "\t" << LIBRARY_NAME << " Version: " << LIBRARY_VERSION << std::endl;
    os << "Time: " << GetDatetimeString() << std::endl;
    os << std::setfill('*') << std::setw(55) << "" << std::endl;
}
