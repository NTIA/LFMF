/** @file ReturnCodes.cpp
 * Maps status messages to library return codes
 */

#include "ITS.TODO-TEMPLATE/ReturnCodes.h"

#include <string>         // for std::string
#include <unordered_map>  // for std::unordered_map

namespace ITS {
// TODO-TEMPLATE: put this function in this software's namespace

/*******************************************************************************
 * Get an error message string from a return code.
 * 
 * @param[in] code  Integer return code.
 * @return          A status message corresponding to the input code.
 ******************************************************************************/
std::string GetReturnStatus(int code) {
    static const std::unordered_map<ReturnCode, std::string> messages = {
        {SUCCESS, "Successful execution"}
        // TODO-TEMPLATE: Add messages corresponding to all return codes here
    };
    // Construct status message
    std::string msg = LIBRARY_NAME;
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

}  // namespace ITS