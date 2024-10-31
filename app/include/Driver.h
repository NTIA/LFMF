/** @file Driver.h
 * Interface header for this driver executable
 */
#ifndef __DRIVER_H__
#define __DRIVER_H__

#include "CommaSeparatedIterator.h"
#include "ReturnCodes.h"
#include "Structs.h"
#include "DriverConfig.h"
#include "ITS.Propagation.LFMF/LFMF.h"

#include <fstream>   // for std::ofstream
#include <iomanip>   // for std::left, std::setw
#include <iostream>  // for std::cout
#include <ostream>   // for std::endl, std::ostream
#include <string>    // for std::string

/////////////////////////////
// Macros

/** Shortcut for concise print-to-file statements in driver */
#define PRINT << std::endl << std::left << std::setw(25) <<
/** Shortcut for setting fixed whitespace padding in driver file output */
#define SETW13 << std::setw(13) <<

//////////////////////////////
// Library Namespace

/////////////////////////////
// Functions
void Help(std::ostream &os = std::cout);
DrvrReturnCode ParseArguments(int argc, char **argv, DrvrParams &params);
DrvrReturnCode ValidateInputs(const DrvrParams &params);

// Driver Utils
std::string GetDatetimeString();
DrvrReturnCode ParseDouble(const std::string &str, double &value);
DrvrReturnCode ParseInteger(const std::string &str, int &value);
void PrintLabel(std::ofstream &fp, const std::string &lbl);
void StringToLower(std::string &str);

void Version(std::ostream &os = std::cout);

#endif