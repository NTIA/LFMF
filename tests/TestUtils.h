/** @file TestUtils.h
 * Primary header for fixtures or common functions used by unit tests.
 */
#pragma once

// clang-format off
// GoogleTest must be included first
#include <gtest/gtest.h>  // GoogleTest
// clang-format on

#include "LFMF.h"

#include <string>  // for std::string

using namespace ITS::Propagation::LFMF;

// Absolute tolerance for comparing double values
constexpr double ABSTOL_DBL = 1.0e-6;

// Absolute tolerance for comparing dB values (model predictions)
constexpr double ABSTOL__DB = 1.0e-1;

// clang-format off
/** Struct for parsing LFMF CSV test data */
struct LFMFTestData {
        double h_tx__meter;    /**< Height of the transmitter, in meters */
        double h_rx__meter;    /**< Height of the receiver, in meters */
        double f__mhz;         /**< Frequency, in MHz */
        double P_tx__watt;     /**< Transmitter power, in watts */
        double N_s;            /**< Surface refractivity, in N-Units */
        double d__km;          /**< Path distance, in km */
        double epsilon;        /**< Relative permittivity */
        double sigma;          /**< Conductivity, in siemens per meter */
        Polarization pol;      /**< Polarization enum value */
        ReturnCode rtn;        /**< Expected Return Code */
        double A_btl__db;      /**< Expected result BTL prediction, in dB */
        double E_dBuVm;        /**< Expected result electric field strength, in dB(uV/m) */
        double P_rx__dbm;      /**< Expected result received power, in dBm */
        SolutionMethod method; /**< Expected result solution method enum value */
};
// clang-format on

std::vector<LFMFTestData> ReadLFMFTestData(const std::string &filename);

void AppendDirectorySep(std::string &str);
std::string GetDataDirectory();