/** @file TestLFMFPolarizationHorizontalMax.cpp
 * Implements the google tests from ITS.Propagation.LFMF.
 */

#include "LFMFGTest.h"

/******************************************************************************
 *
 *  Description:  The purpose of this is to ensure that the LFMF model
 *                executes the same results as matlab code.
 *                Test Data are from https://github.com/eeveetza/LFMFSmoothEarth.
 *  *             Polarization:   Horizontal
 *                Lower antenna:   0, in meter
 *                Higher antenna: 50, in meter
 *
 *****************************************************************************/
class TestLFMFPolarizationHorizontalMax: public ::testing::Test {
    protected:
    void SetUp() override {
        // Load test data from CSV
        testData = ReadLFMFInputsAndResult(fileName);
    }

    // Vector to hold test data
    std::vector<LFMFInputsAndResult> testData;

    std::string fileName = "ValidationPolarizationHorizontalMax.csv";
};

/******************************************************************************
 *
 *  Description:  Test case to verify LFMF Flat earth curve method results are correct
 *
 *****************************************************************************/
TEST_F(TestLFMFPolarizationHorizontalMax, FlatEarthCurveMethodEquivalentToMatLAB) {
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
            compareDouble(data.expectedResult.A_btl__db, result.A_btl__db);
            compareDouble(data.expectedResult.E_dBuVm, result.E_dBuVm);
            compareDouble(data.expectedResult.P_rx__dbm, result.P_rx__dbm);
            EXPECT_EQ(result.method, data.expectedResult.method);
        }
    }
};

/******************************************************************************
 *
 *  Description:  Test case to verify LFMF Residue series method results are correct
 *
 *****************************************************************************/
TEST_F(TestLFMFPolarizationHorizontalMax, ResidueSeriesMethodEquivalentToMatLAB) {
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
            compareDouble(data.expectedResult.A_btl__db, result.A_btl__db);
            compareDouble(data.expectedResult.E_dBuVm, result.E_dBuVm);
            compareDouble(data.expectedResult.P_rx__dbm, result.P_rx__dbm);
            EXPECT_EQ(result.method, data.expectedResult.method);
        }
    }
};
