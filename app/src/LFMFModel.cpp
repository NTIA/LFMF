/** @file LFMFModel.cpp
 * Implements top-level functions for running the Aeronautical Statistical Model.
 */
#include "Driver.h"

// Define the input keys
const std::string LFMFInputKeys::f__ghz = "f__ghz";
const std::string LFMFInputKeys::theta__deg = "theta__deg";
const std::string LFMFInputKeys::p = "p";

/*******************************************************************************
 * Top-level control function for Aeronautical Statistical Model operation
 * 
 * @param[in] asm_params  Aeronautical Statistical Model input parameter struct
 * @param[out] L_ces__db   Basic transmission loss, in dB
 * @return                 Return code
 ******************************************************************************/
ReturnCode CallLFMFModel(
    LFMFParams &asm_params, std::vector<double> &L_ces__db
) {
    ReturnCode rtn;
    double L_ces;
    rtn = LFMFModel(
        asm_params.f__ghz, asm_params.theta__deg, asm_params.p, L_ces
    );
    L_ces__db.push_back(L_ces);

    return rtn;
}

/*******************************************************************************
 * Parse input stream (file or string stream) to LFMF parameter struct.
 * 
 * @param[in]  stream      Path to LFMF input parameter file
 * @param[out] asm_params  LFMF input parameter struct
 * @return                 Return code
 ******************************************************************************/
DrvrReturnCode
    ParseLFMFInputStream(std::istream &stream, LFMFParams &asm_params) {
    CommaSeparatedIterator it(stream);
    DrvrReturnCode rtn = DRVR__SUCCESS;
    std::string key, value, errMsg;
    while (it) {
        std::tie(key, value) = *it;
        if (key.compare(LFMFInputKeys::f__ghz) == 0) {
            rtn = ParseDouble(value, asm_params.f__ghz);
            if (rtn == DRVRERR__PARSE)
                rtn = DRVRERR__PARSE_FREQ;
        } else if (key.compare(LFMFInputKeys::theta__deg) == 0) {
            rtn = ParseDouble(value, asm_params.theta__deg);
            if (rtn == DRVRERR__PARSE)
                rtn = DRVRERR__PARSE_THETA;
        } else if (key.compare(LFMFInputKeys::p) == 0) {
            rtn = ParseDouble(value, asm_params.p);
            if (rtn == DRVRERR__PARSE)
                rtn = DRVRERR__PARSE_PERCENTAGE;
        } else {
            rtn = DRVRERR__PARSE;
        }

        if (rtn != DRVR__SUCCESS) {
            std::cerr << GetDrvrReturnStatus(rtn);
            return rtn;
        }
        ++it;
    }
    return rtn;
}

/*******************************************************************************
 * Parse Aeronautical Statistical Model input parameter file
 * 
 * @param[in]  in_file     Path to LFMF input parameter file
 * @param[out] asm_params  LFMF input parameter struct
 * @return                 Return code
 ******************************************************************************/
DrvrReturnCode
    ParseLFMFInputFile(const std::string &in_file, LFMFParams &asm_params) {
    std::ifstream file(in_file);
    if (!file) {
        std::cerr << "Failed to open file " << in_file << std::endl;
        return DRVRERR__OPENING_INPUT_FILE;
    }
    return ParseLFMFInputStream(file, asm_params);
}

/*******************************************************************************
 * Write Aeronautical Statistical Model inputs to the report file
 * 
 * @param[in] fp      Output stream, a text file open for writing
 * @param[in] params  LFMF input parameter struct
 ******************************************************************************/
void WriteLFMFInputs(std::ofstream &fp, const LFMFParams &params) {
    fp PRINT LFMFInputKeys::f__ghz SETW13 params.f__ghz << "(gigahertz)";
    fp PRINT LFMFInputKeys::theta__deg SETW13 params.theta__deg << "(degrees)";
    fp PRINT LFMFInputKeys::p SETW13 params.p << "(%)";
}