/** @file TestLFMFEquivalence.cpp
 * Implements the google tests from ITS.Propagation.LFMF.
 */

#include "LFMFGTest.h"

/******************************************************************************
 *
 *  Description:  The purpose of this is to ensure that the LFMF model
 *                executes the same results as matlab code.
 *                Test Data are from https://github.com/eeveetza/LFMFSmoothEarth.
 *
 *****************************************************************************/
class TestLFMFEquivalence: public ::testing::Test {
    protected:
    void SetUp() override {
        // Load test data from CSV
        testData = ReadLFMFInputsAndResult(fileName);
    }

    // Vector to hold test data
    std::vector<LFMFInputsAndResult> testData;

    double TOLERANCE = 1.0e-6;
    std::string fileName = "ValidationExampleLFMFSmoothEarth.csv";
};

/******************************************************************************
 *
 *  Description:  Test case to verify LFMF Flat earth curve method results are correct
 *
 *****************************************************************************/
TEST_F(TestLFMFEquivalence, FlatEarthCurveMethodEquivalentToMatLAB) {
    // Ensure test data was loaded
    EXPECT_NE(static_cast<int>(testData.size()), 0);
    int i = 0;
    for (const auto &data : testData) {
        if (data.expectedResult.method == METHOD__FLAT_EARTH_CURVE) {
            i++;
            Result result;
            if (i % 100 == 0) {
                std::cout << " Test instance: " << i << std::endl;
            }
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

            EXPECT_EQ(rtn, SUCCESS);
            EXPECT_NEAR(
                result.A_btl__db, data.expectedResult.A_btl__db, TOLERANCE
            );
            EXPECT_NEAR(result.E_dBuVm, data.expectedResult.E_dBuVm, TOLERANCE);
            EXPECT_NEAR(
                result.P_rx__dbm, data.expectedResult.P_rx__dbm, TOLERANCE
            );
            EXPECT_EQ(result.method, data.expectedResult.method);
        }
    }
    std::cout << "TestLFMF from '" << fileName << "': " << i
              << " Flat Earth Curve Method Test instances." << std::endl;
};

/******************************************************************************
 *
 *  Description:  Test case to verify LFMF Residue series method results are correct
 *
 *****************************************************************************/
TEST_F(TestLFMFEquivalence, ResidueSeriesMethodEquivalentToMatLAB) {
    // Ensure test data was loaded
    EXPECT_NE(static_cast<int>(testData.size()), 0);
    int i = 0;
    for (const auto &data : testData) {
        if (data.expectedResult.method == METHOD__RESIDUE_SERIES) {
            i++;            
            Result result;
            if (i % 100 == 0) {
                std::cout << " Test instance: " << i << std::endl;
            }
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

            EXPECT_EQ(rtn, SUCCESS);
            EXPECT_NEAR(
                result.A_btl__db, data.expectedResult.A_btl__db, TOLERANCE
            );
            EXPECT_NEAR(result.E_dBuVm, data.expectedResult.E_dBuVm, TOLERANCE);
            EXPECT_NEAR(
                result.P_rx__dbm, data.expectedResult.P_rx__dbm, TOLERANCE
            );
            EXPECT_EQ(result.method, data.expectedResult.method);
        }
    }
    std::cout << "TestLFMF from '" << fileName << "': " << i
              << " Residue Series Method Test instances." << std::endl;
};

