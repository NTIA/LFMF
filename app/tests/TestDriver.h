/** @file TestDriver.h
 * Primary header for command line driver tests.
 */
#pragma once

#include "Driver.h"
#include "TempTextFile.h"

#include <cstdlib>  // for std::system
#include <sstream>  // for std::ostringstream
#include <string>   // for std::string
#include <vector>

//////////////////////
// FUNCTIONS

std::string joinArguments(const std::vector<std::string> &args);
void appendDirectorySep(std::string &str);
int ParseInteger(const std::string &str);
