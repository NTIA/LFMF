/** @file ReturnCodes.h
 * Contains return codes used by this software
 */
#pragma once

#include <string>
#include <unordered_map>

namespace ITS {
// TODO-TEMPLATE put this enum in the correct namespace

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

std::string GetReturnStatus(int code);

}  // namespace ITS
