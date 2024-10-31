/** @file Structs.h
 * Contains data structures and type macros used by this software
*/
#ifndef __DRIVER_STRUCTS_H__
#define __DRIVER_STRUCTS_H__

#include <string>  // for std::string

/////////////////////////////
// Data Structures

/** Parameters provided to the command line driver */
struct DrvrParams {
        std::string in_file = "";  /**< Input file */
        std::string out_file = ""; /**< Output file */
        bool DBG = false;          /**< Dump intermediate values to file? */
};

/** Input parameters for the LFMF Model */
struct LFMFParams {
        double f__ghz;     /**< Frequency, in GHz */
        double theta__deg; /**< Elevation angle, in degrees */
        double p;          /**< Percentage of locations */
};

/** Key names for LFMF Model input file parameters */
struct LFMFInputKeys {
        static const std::string f__ghz;     /**< Frequency, in GHz */
        static const std::string theta__deg; /**< Elevation angle, in degrees */
        static const std::string p;          /**< Percentage of locations */
};  // Constants defined in app/src/LFMFModel.cpp

#endif