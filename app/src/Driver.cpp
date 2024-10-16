/** @file Driver.cpp
 * Implements the main function of the executable, and other high-level functions
 */
#include "Driver.h"

/*******************************************************************************
 * Main function of the driver executable
 ******************************************************************************/
int main(int argc, char **argv) {
    int rtn;
    DrvrParams params;

    // Parse command line arguments
    rtn = ParseArguments(argc, argv, params);
    if (rtn == DRVR__RETURN_SUCCESS)
        return SUCCESS;
    if (rtn) {
        Help();
        return rtn;
    }

    // validate command line inputs
    rtn = ValidateInputs(params);
    if (rtn) {
        Help();
        return rtn;
    }

    // TODO-TEMPLATE: Add driver logic, e.g. validating inputs and calling the model

    // Return driver error code if one was returned
    if (rtn >= 1100)
        return rtn;

    // Print results to file
    std::ofstream fp;
    fp.open(params.out_file.c_str());
    if (!fp.is_open()) {
        std::cerr << "Error opening output file. Exiting." << std::endl;
        return DRVRERR__OPENING_OUTPUT_FILE;
    }
    fp << std::left << std::setw(25) << "Model" << LIBRARY_NAME;
    fp PRINT "Library Version" << "v" << LIBRARY_VERSION;
    fp PRINT "Driver Version" << "v" << DRIVER_VERSION;
    fp PRINT "Date Generated" << GetDatetimeString();
    fp PRINT "Input Arguments";
    for (int i = 1; i < argc; i++) {
        fp << argv[i] << " ";
    }
    fp << std::endl << std::endl;
    // TODO-TEMPLATE populate the rest of the output file
    fp.close();
}

/*******************************************************************************
 * Parse the command line arguments
 * 
 * @param[in]  argc    Number of arguments
 * @param[in]  argv    Command line arguments
 * @param[out] params  Structure with user input params
 * @return             Return code
 ******************************************************************************/
int ParseArguments(int argc, char **argv, DrvrParams &params) {
    for (int i = 1; i < argc; i++) {
        std::string arg(argv[i]);
        std::transform(arg.begin(), arg.end(), arg.begin(), [](const char c) {
            return static_cast<char>(std::tolower(c));
        });

        // TODO-TEMPLATE: Specify behavior based on command line arguments.
        // Template code will set in_file and out_file in DrvrParams based on -i
        // and -o options. It will also set DrvrParams.DBG based on a -dbg flag
        // and will call Version() or Help() respectively if -v or -h is given.
        if (arg == "-i") {
            params.in_file = argv[i + 1];
            i++;
        } else if (arg == "-o") {
            params.out_file = argv[i + 1];
            i++;
        } else if (arg == "-dbg") {
            params.DBG = true;
        } else if (arg == "-v") {
            Version();
            return DRVR__RETURN_SUCCESS;
        } else if (arg == "-h") {
            Help();
            return DRVR__RETURN_SUCCESS;
        } else {
            std::cerr << "Unknown option: " << argv[i] << std::endl;
            return DRVRERR__INVALID_OPTION;
        }
    }

    return SUCCESS;
}

/*******************************************************************************
 * Print help instructions to the terminal
 * 
 * @param[in] os  Output stream for writing; defaults to `std::cout`
 ******************************************************************************/
void Help(std::ostream &os) {
    // TODO-TEMPLATE: Update driver help message
    os << std::endl << "Usage: .\\<Driver Executable> [Options]" << std::endl;
    os << "Options (not case sensitive)" << std::endl;
    os << "\t-i    :: Input file name" << std::endl;
    os << "\t-t    :: Terrain file name" << std::endl;
    os << "\t-o    :: Output file name" << std::endl;
    os << "\t-dbg  :: Dump intermediate values to output file [optional]"
       << std::endl;
    os << std::endl << "Examples:" << std::endl;
    os << "\t[WINDOWS] " << DRIVER_NAME
       << ".exe -i inputs.txt -t terrain.txt -o results.txt" << std::endl;
    os << "\t[LINUX]   .\\" << DRIVER_NAME
       << " -i inputs.txt -t terrain.txt -o results.txt" << std::endl;
    os << std::endl;
};

/*******************************************************************************
 * Validate that required inputs are present for the mode specified by the user.
 * 
 * This function DOES NOT check the validity of the parameter values, only that
 * required parameters have been specified by the user
 * 
 * @param[in] params  Structure with user input parameters
 * @return            Return code
 ******************************************************************************/
int ValidateInputs(const DrvrParams &params) {
    // TODO-TEMPLATE: Check that required inputs were provided.
    // This template code checks that input/output files were given with -i and -o
    if (params.in_file.length() == 0)
        return Validate_RequiredErrMsgHelper("-i", DRVRERR__VALIDATION_IN_FILE);

    if (params.out_file.length() == 0)
        return Validate_RequiredErrMsgHelper(
            "-o", DRVRERR__VALIDATION_OUT_FILE
        );

    return SUCCESS;
}
