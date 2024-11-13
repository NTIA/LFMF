/** @file TestDriver.cpp
 * General tests for the driver executable
 */
#include "TestDriver.h"

#include <string>  // for std::string

TEST_F(DriverTest, MissingOptionError1) {
    // Test case: missing option between two provided flags
    std::string cmd = executable + " -i -o out.txt";
    SuppressOutputs(cmd);
    int rtn = RunCommand(cmd);
    EXPECT_EQ(DRVRERR__MISSING_OPTION, rtn);
}

TEST_F(DriverTest, MissingOptionError2) {
    // Test case: missing option at the end of command
    std::string cmd = executable + " -i";
    SuppressOutputs(cmd);
    int rtn = RunCommand(cmd);
    EXPECT_EQ(DRVRERR__MISSING_OPTION, rtn);
}

TEST_F(DriverTest, InvalidOptionError) {
    std::string cmd = executable + " -X";
    SuppressOutputs(cmd);
    int rtn = RunCommand(cmd);
    EXPECT_EQ(DRVRERR__INVALID_OPTION, rtn);
}

TEST_F(DriverTest, OpeningInputFileError) {
    params.in_file = "/invalid/path/input.xyz";
    int rtn = RunDriver(params);
    EXPECT_EQ(DRVRERR__OPENING_INPUT_FILE, rtn);
}

TEST_F(DriverTest, OpeningOutputFileError) {
    // Provide valid inputs but invalid output file path
    std::string inputs = "h_tx__meter,0\nh_rx__meter,0\nf__mhz,0.01\nP_tx__watt,1000\nN_s,301\nd__km,1000\nepsilon,15\nsigma,0.005\npol,0";
    params.out_file = "/invalid/path/output.xyz";
    int rtn = RunDriverWithInputFile(inputs, params);
    EXPECT_EQ(DRVRERR__OPENING_OUTPUT_FILE, rtn);
}

TEST_F(DriverTest, ValidationInFileError) {
    std::string cmd = executable + " -o out.txt";
    SuppressOutputs(cmd);
    int rtn = RunCommand(cmd);
    EXPECT_EQ(DRVRERR__VALIDATION_IN_FILE, rtn);
}

TEST_F(DriverTest, ValidationOutFileError) {
    // Input file does not need to exist here, just has to be specified
    std::string cmd = executable + " -i in.txt";
    SuppressOutputs(cmd);
    int rtn = RunCommand(cmd);
    EXPECT_EQ(DRVRERR__VALIDATION_OUT_FILE, rtn);
}
