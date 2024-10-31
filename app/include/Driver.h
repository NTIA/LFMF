/** @file Driver.h
 * Interface header for this driver executable
 */
#ifndef __DRIVER_H__
#define __DRIVER_H__

#include "CommaSeparatedIterator.h"
#include "Errors.h"
#include "Structs.h"
#include "DriverConfig.h"
#include "ITS.Propagation.LFMF/LFMF.h"

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
using namespace ITS::Propagation::LFMF;

/////////////////////////////
// Functions
int ParseArguments(int argc, char **argv, DrvrParams &params);
void Help(std::ostream &os = std::cout);
int ValidateInputs(const DrvrParams &params);

// Driver Utils
void Version(std::ostream &os = std::cout);
int Validate_RequiredErrMsgHelper(const std::string &opt, const int err);
int ParseInteger(const std::string &str, int &value);
int ParseDouble(const std::string &str, double &value);
int ParsingErrorHelper(const int err, const std::string &msg);
std::string GetDatetimeString();
void StringToLower(std::string &str);

#endif