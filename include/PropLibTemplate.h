/** @file PropLibTemplate.h
 * Interface header for this library
 * // TODO-TEMPLATE: Rename this file to your ${LIB_NAME}
 */
#pragma once

#include <string>         // for std::string
#include <unordered_map>  // for std::unordered_map

// TODO-TEMPLATE: This header should provide EVERYTHING needed to interface
// with the shared library, without needing to include other headers.

namespace ITS {
// TODO-TEMPLATE: Use your library's namespace

// Define cross-platform EXPORTED
#ifndef DOXYGEN_SHOULD_SKIP
    #ifdef _WIN32
        #define EXPORTED extern "C" __declspec(dllexport)
    #else
        #define EXPORTED extern "C"
    #endif
#endif

////////////////////////////////////////////////////////////////////////////////
// Enums

/*******************************************************************************
 * Return Codes defined by this software (0-127)
 ******************************************************************************/
// clang-format off
enum ReturnCode {
    SUCCESS = 0,               /**< Successful execution */

    // TODO-TEMPLATE add return codes for this software
    // TODO-TEMPLATE: Add corresponding status messages in src/ReturnCodes.cpp
};
// clang-format on

////////////////////////////////////////////////////////////////////////////////
// Constants
// TODO-TEMPLATE define any global constants here (use constexpr!)

////////////////////////////////////////////////////////////////////////////////
// Public Functions
// TODO-TEMPLATE: Add functions which should be exported in the DLL
EXPORTED char *GetReturnStatusCharArray(const int code);
EXPORTED void FreeReturnStatusCharArray(char *c_msg);

////////////////////////////////////////////////////////////////////////////////
// Private Functions
// TODO-TEMPLATE: Add other/internal functions here (no need for "EXPORTED")
std::string GetReturnStatus(const int code);

}  // namespace ITS
