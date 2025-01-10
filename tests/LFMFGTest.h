/** @file LFMFGTest.h
 * Interface header for this google test
 */

#ifndef __ITS_PROPAGATION_LFMF_LFMFGTEST_H__
#define __ITS_PROPAGATION_LFMF_LFMFGTEST_H__

#include "gtest/gtest.h"

#include "LFMF.h"

using namespace ITS::Propagation::LFMF;

#define INF std::numeric_limits<double>::infinity()     ///< Infinity in double

/** @struct LFMFInputsAndResult
 * struct Inputs and Outputs for LFMF Model
 */
struct LFMFInputsAndResult {
    double h_tx__meter;     ///<  Height of the transmitter, in meter
    double h_rx__meter;     ///<  Height of the receiver, in meter
    double f__mhz;          ///<  Frequency, in MHz
    double P_tx__watt;      ///<  Transmitter power, in Watts
    double N_s;             ///<  Surface refractivity, in N-Units
    double d__km;           ///<  Path distance, in km
    double epsilon;         ///<  Relative permittivity
    double sigma;           ///<  Conductivity
    int pol;                ///<  Polarization: 0 = Horizontal, 1 = Vertical
    int expectedReturn;     ///<  Expected Return Code
    Result expectedResult;  ///<  Expected Outputs in Result Struct
};

std::vector<LFMFInputsAndResult> ReadLFMFInputsAndResult(const std::string &filename);

std::vector<std::string> readCSVRow(const std::string& row);

std::vector<std::vector<std::string>> readCSV(std::istream& in);

void AppendDirectorySep(std::string& str);

std::string GetDirectory(std::string name);

double stringToDouble(std::string s);

void compareDouble(double expected, double actual, double TOLERANCE=1.0e-6);

#endif