/** @file TestUtils.h
 * Primary header for fixtures or common functions used by unit tests.
 */
#pragma once

// clang-format off
// GoogleTest must be included first
#include <gtest/gtest.h>  // GoogleTest
// clang-format on

// TODO-TEMPLATE: include your library's main interface header here
#include "PropLibTemplate.h"

// TODO-TEMPLATE: define any common test fixtures here
void AppendDirectorySep(std::string &str);
std::string GetDataDirectory();
