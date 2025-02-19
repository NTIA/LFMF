/** @file TestLFMFReturnCode.cpp
 * Test against a set of example cases, including intentionally triggering errors.
 */

#include "TestUtils.h"

/*******************************************************************************
 * These tests evaluate a number of expected input/output combinations against
 * the current version of the LF/MF code, including combinations which are
 * expected to produce specific errors.
 ******************************************************************************/
class TestLFMFReturnCode: public ::testing::Test {
    protected:
        void SetUp() override {
            // Load test data from CSV
            testData = ReadLFMFTestData(fileName);
        }

        // Vector to hold test data
        std::vector<LFMFTestData> testData;

        std::string fileName = "LFMF_Examples.csv";

        // Initialize common output variables
        ReturnCode rtn;
        Result result;
};

/** Test case to verify LFMF results are correct */
TEST_F(TestLFMFReturnCode, ReturnSuccess) {
    // Ensure test data was loaded
    EXPECT_NE(static_cast<int>(testData.size()), 0);
    std::cout << "TestLFMF from '" << fileName << "': " << testData.size()
              << " Test instances." << std::endl;

    for (const auto &data : testData) {
        if (data.rtn == SUCCESS) {
            rtn = LFMF_CPP(
                data.h_tx__meter,
                data.h_rx__meter,
                data.f__mhz,
                data.P_tx__watt,
                data.N_s,
                data.d__km,
                data.epsilon,
                data.sigma,
                data.pol,
                result
            );
            EXPECT_EQ(rtn, data.rtn);
            EXPECT_NEAR(result.A_btl__db, data.A_btl__db, ABSTOL__DB);
            EXPECT_NEAR(result.E_dBuVm, data.E_dBuVm, ABSTOL__DB);
            EXPECT_NEAR(result.P_rx__dbm, data.P_rx__dbm, ABSTOL__DB);
            EXPECT_EQ(result.method, data.method);
        }
    }
}

/** Test case to verify LFMF input TX terminal height is out of range */
TEST_F(TestLFMFReturnCode, InvalidTXTerminalHeight) {
    for (const auto &data : testData) {
        if (data.rtn == ERROR__TX_TERMINAL_HEIGHT) {
            rtn = LFMF_CPP(
                data.h_tx__meter,
                data.h_rx__meter,
                data.f__mhz,
                data.P_tx__watt,
                data.N_s,
                data.d__km,
                data.epsilon,
                data.sigma,
                data.pol,
                result
            );
            EXPECT_EQ(rtn, ERROR__TX_TERMINAL_HEIGHT);
        }
    }
}

/** Test case to verify LFMF input RX terminal height is out of range */
TEST_F(TestLFMFReturnCode, InvalidRXTerminalHeight) {
    for (const auto &data : testData) {
        if (data.rtn == ERROR__RX_TERMINAL_HEIGHT) {
            rtn = LFMF_CPP(
                data.h_tx__meter,
                data.h_rx__meter,
                data.f__mhz,
                data.P_tx__watt,
                data.N_s,
                data.d__km,
                data.epsilon,
                data.sigma,
                data.pol,
                result
            );
            EXPECT_EQ(rtn, ERROR__RX_TERMINAL_HEIGHT);
        }
    }
}

/** Test case to verify LFMF input Frequency is out of range */
TEST_F(TestLFMFReturnCode, InvalidFrequency) {
    for (const auto &data : testData) {
        if (data.rtn == ERROR__FREQUENCY) {
            rtn = LFMF_CPP(
                data.h_tx__meter,
                data.h_rx__meter,
                data.f__mhz,
                data.P_tx__watt,
                data.N_s,
                data.d__km,
                data.epsilon,
                data.sigma,
                data.pol,
                result
            );
            EXPECT_EQ(rtn, ERROR__FREQUENCY);
        }
    }
}

/** Test case to verify LFMF input Transmit power is out of range */
TEST_F(TestLFMFReturnCode, InvalidTransmitPower) {
    for (const auto &data : testData) {
        if (data.rtn == ERROR__TX_POWER) {
            rtn = LFMF_CPP(
                data.h_tx__meter,
                data.h_rx__meter,
                data.f__mhz,
                data.P_tx__watt,
                data.N_s,
                data.d__km,
                data.epsilon,
                data.sigma,
                data.pol,
                result
            );
            EXPECT_EQ(rtn, ERROR__TX_POWER);
        }
    }
}

/** Test case to verify LFMF input Surface refractivity is out of range */
TEST_F(TestLFMFReturnCode, InvalidSurfaceRefractivity) {
    for (const auto &data : testData) {
        if (data.rtn == ERROR__SURFACE_REFRACTIVITY) {
            rtn = LFMF_CPP(
                data.h_tx__meter,
                data.h_rx__meter,
                data.f__mhz,
                data.P_tx__watt,
                data.N_s,
                data.d__km,
                data.epsilon,
                data.sigma,
                data.pol,
                result
            );
            EXPECT_EQ(rtn, ERROR__SURFACE_REFRACTIVITY);
        }
    }
}

/** Test case to verify LFMF input Path distance is out of range */
TEST_F(TestLFMFReturnCode, InvalidPathDistance) {
    for (const auto &data : testData) {
        if (data.rtn == ERROR__PATH_DISTANCE) {
            rtn = LFMF_CPP(
                data.h_tx__meter,
                data.h_rx__meter,
                data.f__mhz,
                data.P_tx__watt,
                data.N_s,
                data.d__km,
                data.epsilon,
                data.sigma,
                data.pol,
                result
            );
            EXPECT_EQ(rtn, ERROR__PATH_DISTANCE);
        }
    }
}

/** Test case to verify LFMF input Epsilon is out of range */
TEST_F(TestLFMFReturnCode, InvalidEpsilon) {
    for (const auto &data : testData) {
        if (data.rtn == ERROR__EPSILON) {
            rtn = LFMF_CPP(
                data.h_tx__meter,
                data.h_rx__meter,
                data.f__mhz,
                data.P_tx__watt,
                data.N_s,
                data.d__km,
                data.epsilon,
                data.sigma,
                data.pol,
                result
            );
            EXPECT_EQ(rtn, ERROR__EPSILON);
        }
    }
}

/** Test case to verify LFMF input Sigma is out of range */
TEST_F(TestLFMFReturnCode, InvalidSigma) {
    for (const auto &data : testData) {
        if (data.rtn == ERROR__SIGMA) {
            rtn = LFMF_CPP(
                data.h_tx__meter,
                data.h_rx__meter,
                data.f__mhz,
                data.P_tx__watt,
                data.N_s,
                data.d__km,
                data.epsilon,
                data.sigma,
                data.pol,
                result
            );
            EXPECT_EQ(rtn, ERROR__SIGMA);
        }
    }
}

/** Test case to verify LFMF input polarization is invalid */
TEST_F(TestLFMFReturnCode, InvalidPolarization) {
    bool polarization_checked = false;
    for (const auto &data : testData) {
        // Run any tests cases which should cause polarization error
        if (data.rtn == ERROR__POLARIZATION) {
            polarization_checked = true;
            rtn = LFMF_CPP(
                data.h_tx__meter,
                data.h_rx__meter,
                data.f__mhz,
                data.P_tx__watt,
                data.N_s,
                data.d__km,
                data.epsilon,
                data.sigma,
                data.pol,
                result
            );
            EXPECT_EQ(rtn, ERROR__POLARIZATION);
        }
    }
    // Ensure this test was exercised by at least one test case
    EXPECT_EQ(polarization_checked, true);
}