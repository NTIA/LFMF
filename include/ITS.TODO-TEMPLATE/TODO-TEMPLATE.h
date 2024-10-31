/** @file TODO-TEMPLATE.h
 * Interface header for this library
 * // TODO-TEMPLATE: Rename this file to your ${LIB_NAME}
 */
#pragma once

// TODO-TEMPLATE add other local includes here
#include "ReturnCodes.h"

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
