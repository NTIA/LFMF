/** @file Driver.h
 * Interface header for this driver executable
 */
#pragma once

#include "CommaSeparatedIterator.h"
#include "ReturnCodes.h"
#include "Structs.h"

// TODO-TEMPLATE: Include your library's main interface header
// #include "ITS.<YOUR_NAMESPACE>/<YOUR_LIBRARY>.h"

#include <fstream>   // for std::ofstream
#include <iomanip>   // for std::setw
#include <iostream>  // for std::cerr, std::cout, std::ostream
#include <ostream>   // for std::endl
#include <string>    // for std::string, std::stoi, std::stod
#include <tuple>     // for std::tie
#include <vector>    // for std::vector

/////////////////////////////
// Macros

/** Shortcut for concise print-to-file statements in driver */
#define PRINT << std::endl << std::left << std::setw(25) <<
/** Shortcut for setting fixed whitespace padding in driver file output */
#define SETW13 << std::setw(13) <<

//////////////////////////////
// Library Namespace
// TODO-TEMPLATE: use the namespace of your library
// using namespace ITS::YourLibraryNamespace::YourLibraryName;

/////////////////////////////
// Functions
void Help(std::ostream &os = std::cout);
DrvrReturnCode ParseArguments(int argc, char **argv, DrvrParams &params);
DrvrReturnCode ValidateInputs(const DrvrParams &params);

// Driver Utils
std::string GetDatetimeString();
DrvrReturnCode ParseDouble(const std::string &str, double &value);
DrvrReturnCode ParseInteger(const std::string &str, int &value);
void StringToLower(std::string &str);
void Version(std::ostream &os = std::cout);