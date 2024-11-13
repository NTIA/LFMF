/** @file LFMFModel.cpp
 * Implements top-level functions for running the Aeronautical Statistical Model.
 */
#include "Driver.h"

// Define the input keys
const std::string LFMFInputKeys::h_tx__meter = "h_tx__meter";
const std::string LFMFInputKeys::h_rx__meter = "h_rx__meter";
const std::string LFMFInputKeys::f__mhz = "f__mhz";
const std::string LFMFInputKeys::P_tx__watt = "p_tx__watt";
const std::string LFMFInputKeys::N_s = "n_s";
const std::string LFMFInputKeys::d__km = "d__km";
const std::string LFMFInputKeys::epsilon = "epsilon";
const std::string LFMFInputKeys::sigma = "sigma";
const std::string LFMFInputKeys::pol = "pol"; 

/*******************************************************************************
 * Top-level control function for LFMF Model
 * 
 * @param[in]  lfmf_params     - LFMF Model input parameter struct
 * @param[out] result          - LFMF Results in Result struct
 * @returns    rtn             - Return code
 ******************************************************************************/
ReturnCode CallLFMFModel(LFMFParams &lfmf_params, Result &result) {
    ReturnCode rtn;
    
    rtn = LFMF(
        lfmf_params.h_tx__meter,
        lfmf_params.h_rx__meter,
        lfmf_params.f__mhz,
        lfmf_params.P_tx__watt,
        lfmf_params.N_s,
        lfmf_params.d__km,
        lfmf_params.epsilon,
        lfmf_params.sigma,
        lfmf_params.pol,
        &result
    );    

    return rtn;
}

/*******************************************************************************
 * Parse input stream (file or string stream) to LFMF parameter struct.
 * 
 * @param[in]  stream      Input stream containing LFMF parameters
 * @param[out] lfmf_params  LFMF input parameter struct
 * @return                 Return code
 ******************************************************************************/
DrvrReturnCode ParseLFMFInputStream(std::istream &stream, LFMFParams &lfmf_params) {
    CommaSeparatedIterator it(stream);
    DrvrReturnCode rtn = DRVR__SUCCESS;
    std::string key, value, errMsg;
    while (it) {
        std::tie(key, value) = *it;
        if (key.compare(LFMFInputKeys::h_tx__meter) == 0) {
            rtn = ParseDouble(value, lfmf_params.h_tx__meter);
            if (rtn == DRVRERR__PARSE)
                rtn = DRVRERR__PARSE_TX_TERMINAL_HEIGHT;
        } else if (key.compare(LFMFInputKeys::h_rx__meter) == 0) {
            rtn = ParseDouble(value, lfmf_params.h_rx__meter);
            if (rtn == DRVRERR__PARSE)
                rtn = DRVRERR__PARSE_RX_TERMINAL_HEIGHT;
        } else if (key.compare(LFMFInputKeys::f__mhz) == 0) {
            rtn = ParseDouble(value, lfmf_params.f__mhz);
            if (rtn == DRVRERR__PARSE)
                rtn = DRVRERR__PARSE_FREQUENCY;
        } else if (key.compare(LFMFInputKeys::P_tx__watt) == 0) {
            rtn = ParseDouble(value, lfmf_params.P_tx__watt);
            if (rtn == DRVRERR__PARSE)
                rtn = DRVRERR__PARSE_TX_POWER;
        } else if (key.compare(LFMFInputKeys::N_s) == 0) {
            rtn = ParseDouble(value, lfmf_params.N_s);
            if (rtn == DRVRERR__PARSE)
                rtn = DRVRERR__PARSE_SURFACE_REFRACTIVITY;
        } else if (key.compare(LFMFInputKeys::d__km) == 0) {
            rtn = ParseDouble(value, lfmf_params.d__km);
            if (rtn == DRVRERR__PARSE)
                rtn = DRVRERR__PARSE_PATH_DISTANCE;
        } else if (key.compare(LFMFInputKeys::epsilon) == 0) {
            rtn = ParseDouble(value, lfmf_params.epsilon);
            if (rtn == DRVRERR__PARSE)
                rtn = DRVRERR__PARSE_EPSILON;
        } else if (key.compare(LFMFInputKeys::sigma) == 0) {
            rtn = ParseDouble(value, lfmf_params.sigma);
            if (rtn == DRVRERR__PARSE)
                rtn = DRVRERR__PARSE_SIGMA;
        } else if (key.compare(LFMFInputKeys::pol) == 0) {
            rtn = ParseInteger(value, lfmf_params.pol);
            if (rtn == DRVRERR__PARSE)
                rtn = DRVRERR__PARSE_POLARIZATION;
        } else {
            std::cerr << "Unknown parameter: " << key << std::endl;
            rtn = DRVRERR__PARSE;
        }

        if (rtn != DRVR__SUCCESS) {
            std::cerr << GetDrvrReturnStatus(rtn) << std::endl;
            return rtn;
        }
        ++it;
    }

    return rtn;
}

/*******************************************************************************
 * Parse LFMF Model input parameter file
 * 
 * @param[in]  in_file     Path to LFMF input parameter file
 * @param[out] lfmf_params  LFMF input parameter struct
 * @return                 Return code
 ******************************************************************************/
DrvrReturnCode
    ParseLFMFInputFile(const std::string &in_file, LFMFParams &lfmf_params) {
    std::ifstream file(in_file);
    if (!file) {
        std::cerr << "Failed to open file " << in_file << std::endl;
        return DRVRERR__OPENING_INPUT_FILE;
    }
    return ParseLFMFInputStream(file, lfmf_params);
}

/*******************************************************************************
 * Write LFMF Model inputs to the report file
 * 
 * @param[in] fp      Output stream, a text file open for writing
 * @param[in] params  LFMF input parameter struct
 ******************************************************************************/
void WriteLFMFInputs(std::ofstream &fp, const LFMFParams &params) {
    fp PRINT LFMFInputKeys::h_tx__meter SETW13 params.h_tx__meter << "[meter]";
    fp PRINT LFMFInputKeys::h_rx__meter SETW13 params.h_rx__meter << "[meter]";
    fp PRINT LFMFInputKeys::f__mhz SETW13 params.f__mhz << "[MHz]";
    fp PRINT LFMFInputKeys::P_tx__watt SETW13 params.P_tx__watt << "[Watts]";
    fp PRINT LFMFInputKeys::N_s SETW13 params.N_s << "[N-Units]";
    fp PRINT LFMFInputKeys::d__km SETW13 params.d__km << "[km]";
    fp PRINT LFMFInputKeys::epsilon SETW13 params.epsilon;
    fp PRINT LFMFInputKeys::sigma SETW13 params.sigma;
    fp PRINT LFMFInputKeys::pol SETW13 params.pol << "[0 = Horizontal, 1 = Vertical]";
}

/*******************************************************************************
 * Write LFMF Model outputs to the report file
 * 
 * @param[in] fp        Output stream, a text file open for writing
 * @param[in] result    LFMF output result struct
 ******************************************************************************/
void WriteLFMFOutputs(std::ofstream &fp, const Result &result) {
    fp PRINT "Basic transmission loss" SETW13 std::fixed
        << std::setprecision(2) << result.A_btl__db << "[dB]";
    fp PRINT "Electrice field strength" SETW13 std::fixed
        << std::setprecision(2) << result.E_dBuVm << "[dB(uV/m)]";
    fp PRINT "Received power" SETW13 std::fixed
        << std::setprecision(2) << result.P_rx__dbm << "[dB]";
    fp PRINT "Solution method" SETW13 std::fixed
        << std::setprecision(0) << result.method
        << "[0 = Flat earth with curve correction, 1 = Residue series]";
}