/** @file ReturnCodes.cpp
 * Maps status messages to library return codes
 */

#include "ITS.Propagation.LFMF/LFMF.h"

#ifdef _WIN32
    // Ensure strcpy_s is available on Windows
    #ifndef __STDC_LIB_EXT1__
        #define __STDC_LIB_EXT1__
    #endif
    #ifndef __STDC_WANT_LIB_EXT1__
        #define __STDC_WANT_LIB_EXT1__ 1
    #endif
#endif

#include <cstring>        // for strcpy_s
#include <string>         // for std::string
#include <unordered_map>  // for std::unordered_map

namespace ITS {
namespace Propagation {
namespace LFMF {

/*******************************************************************************
 * Get an error message string from a return code.
 * 
 * @param[in] code  Integer return code.
 * @return          A status message corresponding to the input code.
 ******************************************************************************/
std::string GetReturnStatus(int code) {
    static const std::unordered_map<ReturnCode, std::string> messages = {
        {SUCCESS, "Successful execution"},
        {ERROR__TX_TERMINAL_HEIGHT, "TX terminal height is out of range"},
        {ERROR__RX_TERMINAL_HEIGHT, "RX terminal height is out of range"},
        {ERROR__FREQUENCY, "Frequency is out of range"},
        {ERROR__TX_POWER, "Transmit power is out of range"},
        {ERROR__SURFACE_REFRACTIVITY, "Surface refractivity is out of range"},
        {ERROR__PATH_DISTANCE, "Path distance is out of range"},
        {ERROR__EPSILON, "Epsilon is out of range"},
        {ERROR__SIGMA, "Sigma is out of range"},
        {ERROR__POLARIZATION, "Invalid value for polarization"},
    };
    // Construct status message
    std::string msg = LIBRARY_NAME;
    msg += " v";
    msg += LIBRARY_VERSION;
    if (code == SUCCESS) {
        msg += " Status: ";
    } else {
        msg += " Error: ";
    }

    auto it = messages.find(static_cast<ReturnCode>(code));
    if (it != messages.end()) {
        msg += it->second;
    } else {
        msg += "Undefined return code";
    }
    return msg;
}

/*******************************************************************************
 * Get an error message string (as C-style string) from a return code.
 * 
 * @param[in] code  Integer return code.
 * @return          A status message corresponding to the input code.
 ******************************************************************************/
DLLEXPORT char *GetReturnStatusCharArray(const int code) {
    const std::string msg = GetReturnStatus(code);
    char *c_msg = new char[msg.size() + 1];
#ifdef _WIN32
    strcpy_s(c_msg, msg.size() + 1, msg.c_str());
#else
    strcpy(c_msg, msg.c_str());
#endif
    return c_msg;
}

/*******************************************************************************
 * Free the memory allocated by GetReturnStatusCharArray
 * 
 * @param[in] c_msg  The status message C-style string to delete
 ******************************************************************************/
DLLEXPORT void FreeReturnStatusCharArray(char *c_msg) {
    delete[] c_msg;
}

}  // namespace LFMF
}  // namespace Propagation
}  // namespace ITS
