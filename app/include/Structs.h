/** @file Structs.h
 * Contains data structures and type macros used by this software
*/
#pragma once

#include <string>  // for std::string

/////////////////////////////
// Enums

// TODO-TEMPLATE: If PropLib has more than one export models/functions
/** Valid values of "model" command line option */
enum class PropLibModel {
    NOT_SET = -1,  ///< Invalid model selection
};

/////////////////////////////
// Data Structures

// TODO-TEMPLATE: Basic struct provided to hold input/output file names and DBG flag
/** Parameters provided to the command line driver */
struct DrvrParams {
    std::string in_file = "";   ///< Input file
    std::string out_file = "";  ///< Output file
    bool DBG = false;           ///< Dump intermediate values to file?
    PropLibModel model = PropLibModel::NOT_SET;
};