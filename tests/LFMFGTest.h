/** @file LFMFGTest.h
 * Interface header for this google test
 */

#ifndef __ITS_PROPAGATION_LFMF_LFMFGTEST_H__
#define __ITS_PROPAGATION_LFMF_LFMFGTEST_H__

#include "gtest/gtest.h"

#include "ITS.Propagation.LFMF/LFMF.h"

using namespace ITS::Propagation::LFMF;

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

static void AppendDirectorySep(std::string& str);

static std::string GetDirectory(std::string name);
#endif