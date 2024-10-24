/** @file TestDriver.cpp
 * General tests for the driver executable
 */
#include "TestDriver.h"

TEST_F(DriverTest, MissingOptionError1) {
    // Test case: missing option between two provided flags
    std::string cmd = executable + " -i -o out.txt";
    SuppressOutputs(cmd);
    int rtn = std::system(cmd.c_str());
    EXPECT_EQ(rtn, DRVRERR__MISSING_OPTION);
}

TEST_F(DriverTest, MissingOptionError2) {
    // Test case: missing option at the end of command
    std::string cmd = executable + " -i";
    SuppressOutputs(cmd);
    int rtn = std::system(cmd.c_str());
    EXPECT_EQ(rtn, DRVRERR__MISSING_OPTION);
}

TEST_F(DriverTest, InvalidOptionError) {
    std::string cmd = executable + " -X";
    SuppressOutputs(cmd);
    int rtn = std::system(cmd.c_str());
    EXPECT_EQ(rtn, DRVRERR__INVALID_OPTION);
}

TEST_F(DriverTest, OpeningInputFileError) {
    // TODO-TEMPLATE: Update this call to RunDriver
    params.in_file = "/invalid/path/input.xyz";
    params.DBG = false;
    int rtn = RunDriver(params);
    EXPECT_EQ(rtn, DRVRERR__OPENING_INPUT_FILE);
}

TEST_F(DriverTest, OpeningOutputFileError) {
    // TODO-TEMPLATE: Update this call to RunDriverWithInputFile
    // Provide valid inputs but invalid output file path
    std::string inputs = "template,0.0";
    params.DBG = true;
    params.out_file = "/invalid/path/output.xyz";
    int rtn = RunDriverWithInputFile(inputs, params);
    EXPECT_EQ(rtn, DRVRERR__OPENING_OUTPUT_FILE);
}

TEST_F(DriverTest, ValidationInFileError) {
    std::string cmd = executable + " -o out.txt";
    SuppressOutputs(cmd);
    int rtn = std::system(cmd.c_str());
    EXPECT_EQ(rtn, DRVRERR__VALIDATION_IN_FILE);
}

TEST_F(DriverTest, ValidationOutFileError) {
    // Input file does not need to exist here, just has to be specified
    // TODO-TEMPLATE May need to update the command here
    std::string cmd = executable + " -i in.txt";
    SuppressOutputs(cmd);
    int rtn = std::system(cmd.c_str());
    EXPECT_EQ(rtn, DRVRERR__VALIDATION_OUT_FILE);
}

// TODO-TEMPLATE: Add tests for any additional validation errors

// TODO-TEMPALTE: Add other general tests for the driver