/** @file TestUtils.cpp
 * Primary implementations for fixtures or common functions used by unit tests.
 */
#include "TestUtils.h"

#include <fstream>  // for std::ifstream
#include <sstream>  // for std::istringstream
#include <string>   // for std::string, std::getline
#include <vector>   // for std::vector

/*******************************************************************************
 * Append a directory separator ('/' or '\') to a string, based on the
 * current operating system.
 *
 * @param[in, out] str  String to which the character will be appended.
 ******************************************************************************/
void AppendDirectorySep(std::string &str) {
#ifdef _WIN32
    str += "\\";
#else
    str += "/";
#endif
}

/******************************************************************************
 * Get the full path of the directory containing test data files.
 * 
 * @return The path of the test data directory.
 ******************************************************************************/
std::string GetDataDirectory() {
    std::string dataDir(__FILE__);
    dataDir.resize(dataDir.find_last_of("/\\"));
    dataDir.resize(dataDir.find_last_of("/\\"));
    AppendDirectorySep(dataDir);
    dataDir += "extern";
    AppendDirectorySep(dataDir);
    dataDir
        += "test-data";  // Name of data directory as cloned in the `extern` directory
    AppendDirectorySep(dataDir);
    return dataDir;
}

/*******************************************************************************
 * Loads test data from a CSV file
 *
 * @param[in] filename  Test data CSV file name
 * @return              A vector including all inputs and outputs from the CSV
 *                      in `LFMFTestData` structures.
 ******************************************************************************/
std::vector<LFMFTestData> ReadLFMFTestData(const std::string &filename) {
    std::vector<LFMFTestData> testData;
    std::string dataDir = GetDataDirectory();
    std::ifstream file(dataDir + filename);
    std::string line;
    // struct to store data from a single line of CSV:
    LFMFTestData d;
    char c;  // single character representing the comma (delimiter)
    // Integers to temporarily store enum values before casting
    int pol_value;
    int rtn_value;
    int method_value;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        if (iss >> d.h_tx__meter >> c >> d.h_rx__meter >> c >> d.f__mhz >> c
            >> d.P_tx__watt >> c >> d.N_s >> c >> d.d__km >> c >> d.epsilon >> c
            >> d.sigma >> c >> pol_value >> c >> rtn_value >> c >> d.A_btl__db
            >> c >> d.E_dBuVm >> c >> d.P_rx__dbm >> c >> method_value) {
            // Convert integers to enum
            d.pol = static_cast<Polarization>(pol_value);
            d.rtn = static_cast<ReturnCode>(rtn_value);
            d.method = static_cast<SolutionMethod>(method_value);
            testData.push_back(d);
        }
    }
    return testData;
}

/*******************************************************************************
 * Loads test data from a CSV file located in `tests/data`. The column structure
 * of files used for validation is different from the LFMF-test-data structure.
 *
 * @param[in] filename  Test data CSV file name
 * @return              A vector including all inputs and outputs from the CSV
 *                      in `LFMFTestData` structures.
 ******************************************************************************/
std::vector<LFMFTestData> ReadLFMFValidationData(const std::string &filename) {
    std::vector<LFMFTestData> testData;
    std::string dataDir = GetLocalDataDirectory();
    std::ifstream file(dataDir + filename);
    std::string line;
    // struct to store data from a single line of CSV:
    LFMFTestData d;
    char c;  // single character representing the comma (delimiter)
    // Integers to temporarily store enum values before casting
    int pol_value;
    int rtn_value;
    int method_value;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        if (iss >> d.h_tx__meter >> c >> d.h_rx__meter >> c >> d.f__mhz >> c
            >> d.P_tx__watt >> c >> d.N_s >> c >> d.d__km >> c >> d.epsilon >> c
            >> d.sigma >> c >> pol_value >> c >> d.A_btl__db >> c >> d.E_dBuVm
            >> c >> d.P_rx__dbm >> c >> method_value >> c >> rtn_value) {
            // Convert integers to enum
            d.pol = static_cast<Polarization>(pol_value);
            d.rtn = static_cast<ReturnCode>(rtn_value);
            d.method = static_cast<SolutionMethod>(method_value);
            testData.push_back(d);
        }
    }
    return testData;
}

/******************************************************************************
 * Get the full path of the directory containing validation data files.
 * 
 * @return The path `tests/data/`
 ******************************************************************************/
std::string GetLocalDataDirectory() {
    std::string dataDir(__FILE__);
    dataDir.resize(dataDir.find_last_of("/\\"));
    AppendDirectorySep(dataDir);
    dataDir += "data";
    AppendDirectorySep(dataDir);
    std::cerr << "****************************************\n***************************************";
    std::cerr << dataDir;
    std::cerr << "****************************************\n***************************************";
    return dataDir;
}