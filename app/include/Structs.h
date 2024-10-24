/** @file Structs.h
 * Contains data structures and type macros used by this software
*/
#pragma once

#include <string>  // For std::string

/////////////////////////////
// Data Structures

// TODO-TEMPLATE: Basic struct provided to hold input/output file names and DBG flag
struct DrvrParams {
        std::string in_file = "";  /**< Input file */
        std::string out_file = ""; /**< Output file */
        bool DBG = false;          /**< Dump intermediate values to file? */
};