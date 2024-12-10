/** @file TestLFMFReturnCode.cpp
 * Implements the google tests from ITS.Propagation.LFMF.
 */

#include "LFMFGTest.h"

/******************************************************************************
 *
 *  Description:  The purpose of this is to ensure that CMAKE compiles
 *                the LFMF model DLL correctly.
 *                Test Data are stored in CSV format.
 *
 *****************************************************************************/
class TestLFMFReturnCode : public ::testing::Test {
protected:
    void SetUp() override {
        // Load test data from CSV
        testData = ReadLFMFInputsAndResult(fileName);
    }

    // Vector to hold test data
    std::vector<LFMFInputsAndResult> testData;

    double TOLERANCE = 1.0e-1;
    std::string fileName = "LFMF_Examples.csv";
};

/******************************************************************************
 *
 *  Description:  Test case to verify LFMF results are correct
 *
 *****************************************************************************/
TEST_F(TestLFMFReturnCode, ReturnSuccess) {
    // Ensure test data was loaded
    EXPECT_NE(static_cast<int>(testData.size()), 0);
    std::cout << "TestLFMF from '" << fileName << "': " << testData.size() << " Test instances." << std::endl;

    for (const auto& data : testData) {
        if (data.expectedReturn == SUCCESS) {
            Result result;

            int rtn = LFMF(
                data.h_tx__meter,
                data.h_rx__meter,
                data.f__mhz,
                data.P_tx__watt,
                data.N_s,
                data.d__km,
                data.epsilon,
                data.sigma,
                data.pol,
                &result
            );

            EXPECT_EQ(rtn, data.expectedReturn);
            EXPECT_NEAR(result.A_btl__db, data.expectedResult.A_btl__db, TOLERANCE);
            EXPECT_NEAR(result.E_dBuVm, data.expectedResult.E_dBuVm, TOLERANCE);
            EXPECT_NEAR(result.P_rx__dbm, data.expectedResult.P_rx__dbm, TOLERANCE);
            EXPECT_EQ(result.method, data.expectedResult.method);
        }
    }
}

/******************************************************************************
 *
 *  Description:  Test case to verify LFMF input TX terminal height is out of range
 *
 *****************************************************************************/
TEST_F(TestLFMFReturnCode, InvalidTXTerminalHeight) {
    for (const auto &data : testData) {
        if (data.expectedReturn == ERROR__TX_TERMINAL_HEIGHT) {
            Result result;

            int rtn = LFMF(
                data.h_tx__meter,
                data.h_rx__meter,
                data.f__mhz,
                data.P_tx__watt,
                data.N_s,
                data.d__km,
                data.epsilon,
                data.sigma,
                data.pol,
                &result
            );

            EXPECT_EQ(rtn, ERROR__TX_TERMINAL_HEIGHT);
        }
    }
}

/******************************************************************************
 *
 *  Description:  Test case to verify LFMF input RX terminal height is out of range
 *
 *****************************************************************************/
TEST_F(TestLFMFReturnCode, InvalidRXTerminalHeight) {
    for (const auto &data : testData) {
        if (data.expectedReturn == ERROR__RX_TERMINAL_HEIGHT) {
            Result result;

            int rtn = LFMF(
                data.h_tx__meter,
                data.h_rx__meter,
                data.f__mhz,
                data.P_tx__watt,
                data.N_s,
                data.d__km,
                data.epsilon,
                data.sigma,
                data.pol,
                &result
            );

            EXPECT_EQ(rtn, ERROR__RX_TERMINAL_HEIGHT);
        }
    }
}

/******************************************************************************
 *
 *  Description:  Test case to verify LFMF input Frequency is out of range
 *
 *****************************************************************************/
    TEST_F(TestLFMFReturnCode, InvalidFrequency) {
    for (const auto &data : testData) {
        if (data.expectedReturn == ERROR__FREQUENCY) {
            Result result;

            int rtn = LFMF(
                data.h_tx__meter,
                data.h_rx__meter,
                data.f__mhz,
                data.P_tx__watt,
                data.N_s,
                data.d__km,
                data.epsilon,
                data.sigma,
                data.pol,
                &result
            );

            EXPECT_EQ(rtn, ERROR__FREQUENCY);
        }
    }
}

/******************************************************************************
 *
 *  Description:  Test case to verify LFMF input Transmit power is out of range
 *
 *****************************************************************************/
TEST_F(TestLFMFReturnCode, InvalidTransmitPower) {
    for (const auto &data : testData) {
        if (data.expectedReturn == ERROR__TX_POWER) {
            Result result;

            int rtn = LFMF(
                data.h_tx__meter,
                data.h_rx__meter,
                data.f__mhz,
                data.P_tx__watt,
                data.N_s,
                data.d__km,
                data.epsilon,
                data.sigma,
                data.pol,
                &result
            );

            EXPECT_EQ(rtn, ERROR__TX_POWER);
        }
    }
}

/******************************************************************************
 *
 *  Description:  Test case to verify LFMF input Surface refractivity is out of range
 *
 *****************************************************************************/
TEST_F(TestLFMFReturnCode, InvalidSurfaceRefractivity) {
    for (const auto &data : testData) {
        if (data.expectedReturn == ERROR__SURFACE_REFRACTIVITY) {
            Result result;

            int rtn = LFMF(
                data.h_tx__meter,
                data.h_rx__meter,
                data.f__mhz,
                data.P_tx__watt,
                data.N_s,
                data.d__km,
                data.epsilon,
                data.sigma,
                data.pol,
                &result
            );

            EXPECT_EQ(rtn, ERROR__SURFACE_REFRACTIVITY);
        }
    }
}

/******************************************************************************
 *
 *  Description:  Test case to verify LFMF input Path distance is out of range
 *
 *****************************************************************************/
TEST_F(TestLFMFReturnCode, InvalidPathDistance) {
    for (const auto &data : testData) {
        if (data.expectedReturn == ERROR__PATH_DISTANCE) {
            Result result;

            int rtn = LFMF(
                data.h_tx__meter,
                data.h_rx__meter,
                data.f__mhz,
                data.P_tx__watt,
                data.N_s,
                data.d__km,
                data.epsilon,
                data.sigma,
                data.pol,
                &result
            );

            EXPECT_EQ(rtn, ERROR__PATH_DISTANCE);
        }
    }
}

/******************************************************************************
 *
 *  Description:  Test case to verify LFMF input Epsilon is out of range
 *
 *****************************************************************************/
TEST_F(TestLFMFReturnCode, InvalidEpsilon) {
    for (const auto &data : testData) {
        if (data.expectedReturn == ERROR__EPSILON) {
            Result result;

            int rtn = LFMF(
                data.h_tx__meter,
                data.h_rx__meter,
                data.f__mhz,
                data.P_tx__watt,
                data.N_s,
                data.d__km,
                data.epsilon,
                data.sigma,
                data.pol,
                &result
            );

            EXPECT_EQ(rtn, ERROR__EPSILON);
        }
    }
}

/******************************************************************************
 *
 *  Description:  Test case to verify LFMF input Sigma is out of range
 *
 *****************************************************************************/
TEST_F(TestLFMFReturnCode, InvalidSigma) {
    for (const auto &data : testData) {
        if (data.expectedReturn == ERROR__SIGMA) {
            Result result;

            int rtn = LFMF(
                data.h_tx__meter,
                data.h_rx__meter,
                data.f__mhz,
                data.P_tx__watt,
                data.N_s,
                data.d__km,
                data.epsilon,
                data.sigma,
                data.pol,
                &result
            );

            EXPECT_EQ(rtn, ERROR__SIGMA);
        }
    }
}

/******************************************************************************
 *
 *  Description:  Test case to verify LFMF input polarization is invalid
 *
 *****************************************************************************/
TEST_F(TestLFMFReturnCode, InvalidPolarization) {
    for (const auto &data : testData) {
        Result result;

        int rtn = LFMF(
            data.h_tx__meter,
            data.h_rx__meter,
            data.f__mhz,
            data.P_tx__watt,
            data.N_s,
            data.d__km,
            data.epsilon,
            data.sigma,
            -1,
            &result
        );

        EXPECT_EQ(rtn, ERROR__POLARIZATION);

        rtn = LFMF(
            data.h_tx__meter,
            data.h_rx__meter,
            data.f__mhz,
            data.P_tx__watt,
            data.N_s,
            data.d__km,
            data.epsilon,
            data.sigma,
            3,
            &result
        );

        EXPECT_EQ(rtn, ERROR__POLARIZATION);
        if (data.expectedReturn == ERROR__POLARIZATION) {
            Result result;

            int rtn = LFMF(
                data.h_tx__meter,
                data.h_rx__meter,
                data.f__mhz,
                data.P_tx__watt,
                data.N_s,
                data.d__km,
                data.epsilon,
                data.sigma,
                data.pol,
                &result
            );

            EXPECT_EQ(rtn, ERROR__POLARIZATION);
        }
    }
}