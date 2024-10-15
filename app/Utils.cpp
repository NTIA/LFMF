/** @file Utils.cpp
 * Implements various model-agnostic utility functions for the driver
 */
#include "Driver.h"

/*******************************************************************************
 * Print version information to the specified output stream 
 * 
 * @param[in] os  Output stream for writing; defaults to `std::cout`
 ******************************************************************************/
void Version(std::ostream &os = std::cout) {
    os << std::setfill('*') << std::setw(55) << "" << std::endl;
    os << "Institute for Telecommunication Sciences - Boulder, CO" << std::endl;
    os << "\tDriver Version: " << DRIVER_VERSION << std::endl;
    os << "\t" << LIBRARY_NAME << " Version: " << LIBRARY_VERSION << std::endl;
    os << "Time: " << GetDatetimeString() << std::endl;
    os << std::setfill('*') << std::setw(55) << "" << std::endl;
}

/*******************************************************************************
 * Helper function to format and print error messages encountered during
 * validation of input parameters
 * 
 * @param[in] opt  Command flag in error
 * @param[in] err  Error code
 * @return         Return code
 ******************************************************************************/
int Validate_RequiredErrMsgHelper(const std::string &opt, int err) {
    std::cerr << "Driver Error " << err << ": Option \"" << opt
              << "\" is required but was not provided" << std::endl;
    return err;
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
 * Common error handling function
 * 
 * @param[in] err  Error parsing code
 * @param[in] msg  Error message
 * @return         Error code from input param
 ******************************************************************************/
int ParsingErrorHelper(int err, const std::string &msg) {
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