/** @file TestDriverUtils.cpp
 * Utility functions for the TestDriver executable
 */

#include "TestDriver.h"

#include <stdexcept>

std::string joinArguments(const std::vector<std::string> &args) {
    std::ostringstream oss;
    for (std::string arg : args) {
        oss << arg + " ";
    }
    return oss.str();
}

void appendDirectorySep(std::string &str) {
#ifdef _WIN32
    str += "\\";
#else
    str += "/";
#endif
}

/*******************************************************************************
 * Parse an integer value from the input string
 * 
 * @param[in]  str    Input value as string
 * @return            Parsed integer value
 ******************************************************************************/
int ParseInteger(const std::string &str) {
    int value;
    try {
        size_t pos;
        value = std::stoi(str, &pos, 10);

        // Verify the entire string was parsed
        if (pos != str.size()) {
            throw std::invalid_argument(
                "Input string contains non-numeric characters"
            );
        }
    } catch (...) {
        // error parsing the input string value
        throw std::runtime_error("Could not parse integer value");
    };

    return SUCCESS;
}