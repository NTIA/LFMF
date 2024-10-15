/** @file Driver.h
 * Interface header for this driver executable
 */
#pragma once

#include "Errors.h"
#include "Structs.h"

// TODO-TEMPLATE: Include your library's main interface header
// #include "ITS.<YOUR_NAMESPACE>/<YOUR_LIBRARY>.h"

#include <algorithm>  // for transform
#include <cctype>     // for tolower
#include <cstring>    // for strlen
#include <ctime>     // for localtime_s, localtime_r, time, time_t, tm, strftime
#include <fstream>   // for ifstream, ofstream
#include <iomanip>   // for setw
#include <iostream>  // for cerr, cout
#include <string>    // for string, stoi, stod

/////////////////////////////
// Macros

// Make print-to-file statements more concise in driver
#define PRINT << std::endl << std::left << std::setw(25) <<
#define SETW13 << std::setw(13) <<

// TODO-TEMPLATE: use the namespace of your library
// using namespace ITS::YourLibraryNamespace::YourLibraryName;

/////////////////////////////
// Functions

int ParseArguments(int argc, char **argv, DrvrParams &params);
void Help();
int ValidateInputs(const DrvrParams &params);


// Utils
void Version();
int Validate_RequiredErrMsgHelper(const char *opt, int err);
int ParseInteger(const char *str, int &value);
int ParseDouble(const char *str, double &value);
int ParsingErrorHelper(int err, const char *msg);
std::string GetDatetimeString();