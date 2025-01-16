#include "TestDriver.h"

#include <string>  // for std::string

/*******************************************************************************
 * Driver test fixture for the LFMF Model
 ******************************************************************************/
class LFMFDriverTest: public DriverTest {
    protected:
        void SetUp() override {
            DriverTest::SetUp();
            lfmf_params.out_file = params.out_file;
        }
        void TestLFMF(const std::string &inputs, const int expected_rtn) {
            int lfmf_rtn;
            lfmf_rtn = RunDriverWithInputFile(inputs, lfmf_params);
            EXPECT_EQ(lfmf_rtn, expected_rtn);
        }

        std::string LFMFInputs; /**< String to hold input file contents */
        DrvrParams lfmf_params; /**< Default command line arguments */
};

TEST_F(LFMFDriverTest, TestSuccess) {
    LFMFInputs
        = "h_tx__meter,0\nh_rx__meter,0\nf__mhz,0.01\nP_tx__watt,1000\nN_s,"
          "301\nd__km,1000\nepsilon,15\nsigma,0.005\npol,0";
    TestLFMF(LFMFInputs, SUCCESS);
}

TEST_F(LFMFDriverTest, TestParseError) {
    LFMFInputs = "unknown_param,0.0";
    TestLFMF(LFMFInputs, DRVRERR__PARSE);
}

TEST_F(LFMFDriverTest, TestParseTXTerminalHeightError) {
    LFMFInputs = "h_tx__meter,invalid";
    TestLFMF(LFMFInputs, DRVRERR__PARSE_TX_TERMINAL_HEIGHT);
}

TEST_F(LFMFDriverTest, TestParseRXTerminalHeightError) {
    LFMFInputs = "h_rx__meter,invalid";
    TestLFMF(LFMFInputs, DRVRERR__PARSE_RX_TERMINAL_HEIGHT);
}

TEST_F(LFMFDriverTest, TestParseFrequencyError) {
    LFMFInputs = "f__mhz,invalid";
    TestLFMF(LFMFInputs, DRVRERR__PARSE_FREQUENCY);
}

TEST_F(LFMFDriverTest, TestParseTXPowerError) {
    LFMFInputs = "P_tx__watt,invalid";
    TestLFMF(LFMFInputs, DRVRERR__PARSE_TX_POWER);
}

TEST_F(LFMFDriverTest, TestParseSurfaceRefractivityError) {
    LFMFInputs = "N_s,invalid";
    TestLFMF(LFMFInputs, DRVRERR__PARSE_SURFACE_REFRACTIVITY);
}

TEST_F(LFMFDriverTest, TestParsePathDistanceError) {
    LFMFInputs = "d__km,invalid";
    TestLFMF(LFMFInputs, DRVRERR__PARSE_PATH_DISTANCE);
}

TEST_F(LFMFDriverTest, TestParseEpsilonError) {
    LFMFInputs = "epsilon,invalid";
    TestLFMF(LFMFInputs, DRVRERR__PARSE_EPSILON);
}

TEST_F(LFMFDriverTest, TestParseSigmaError) {
    LFMFInputs = "sigma,invalid";
    TestLFMF(LFMFInputs, DRVRERR__PARSE_SIGMA);
}

TEST_F(LFMFDriverTest, TestParsePolarizationError) {
    LFMFInputs = "pol,invalid";
    TestLFMF(LFMFInputs, DRVRERR__PARSE_POLARIZATION);
}