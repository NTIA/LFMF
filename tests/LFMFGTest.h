/** @file LFMFGTest.h
 * Interface header for this google test
 */

#pragma once
#ifndef __ITS_PROPAGATION_LFMF_LFMFGTEST_H__
#define __ITS_PROPAGATION_LFMF_LFMFGTEST_H__

#include "gtest/gtest.h"

#include "ITS.Propagation.LFMF/LFMF.h"

using namespace ITS::Propagation::LFMF;

struct LFMFInputsAndResult {
    double f__ghz;
    double h_1__km;
    double h_2__km;
    double beta_1__rad;
    int atmosphere;
    int expectedReturn;
    Result expectedResult;
};

std::vector<LFMFInputsAndResult> ReadLFMFInputsAndResult(const std::string &filename);

std::vector<std::string> readCSVRow(const std::string& row);

std::vector<std::vector<std::string>> readCSV(std::istream& in);

static void AppendDirectorySep(std::string& str);

static std::string GetDirectory(std::string name);
#endif