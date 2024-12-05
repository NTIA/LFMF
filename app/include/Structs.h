/** @file Structs.h
 * Contains data structures and type macros used by this software
*/
#ifndef __LFMF_DRIVER_STRUCTS_H__
#define __LFMF_DRIVER_STRUCTS_H__

/////////////////////////////
// Data Structures

/** Parameters provided to the command line driver */
struct DrvrParams {
        std::string in_file = "";  /**< Input file */
        std::string out_file = ""; /**< Output file */
};

/** Input parameters for the LFMF Model */
struct LFMFParams {
        double h_tx__meter;     ///<  Height of the transmitter, in meter
        double h_rx__meter;     ///<  Height of the receiver, in meter
        double f__mhz;          ///<  Frequency, in MHz
        double P_tx__watt;      ///<  Transmitter power, in Watts
        double N_s;             ///<  Surface refractivity, in N-Units
        double d__km;           ///<  Path distance, in km
        double epsilon;         ///<  Relative permittivity
        double sigma;           ///<  Conductivity
        ITS::Propagation::LFMF::Polarization
            pol;  ///<  Polarization: 0 = Horizontal, 1 = Vertical
};

/** Key names for LFMF Model input file parameters */
struct LFMFInputKeys {
        static const std::string h_tx__meter;   ///<  Height of the transmitter, in meter
        static const std::string h_rx__meter;   ///<  Height of the receiver, in meter
        static const std::string f__mhz;        ///<  Frequency, in MHz
        static const std::string P_tx__watt;    ///<  Transmitter power, in Watts
        static const std::string N_s;           ///<  Surface refractivity, in N-Units
        static const std::string d__km;         ///<  Path distance, in km
        static const std::string epsilon;       ///<  Relative permittivity
        static const std::string sigma;         ///<  Conductivity
        static const std::string pol;           ///<  Polarization
};  // Constants defined in app/src/LFMFModel.cpp

#endif