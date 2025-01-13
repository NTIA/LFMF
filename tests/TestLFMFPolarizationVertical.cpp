/** @file TestLFMFPolarizationVertical.cpp
 * TODO
 */

#include "TestUtils.h"

/*******************************************************************************
 * These tests, disabled by default, test this library against results generated
 * by an an external, independently-developed MATLAB implementation. These are
 * used during refactoring to ensure no breaking changes were accidentally made.
 ******************************************************************************/
class TestLFMFPolarizationVertical: public ::testing::Test {
    protected:
        void SetUp() override {
            // Load test data from CSV
            testData = ReadLFMFValidationData(fileName);
        }

        // Vector to hold test data
        std::vector<LFMFTestData> testData;

        std::string fileName = "ValidationPolarizationVertical.csv";
};

/** Test case to verify LFMF Flat earth curve method results are correct */
TEST_F(TestLFMFPolarizationVertical, FlatEarthCurveMethodEquivalentToMatLAB) {
    // Ensure test data was loaded
    EXPECT_NE(static_cast<int>(testData.size()), 0);
    for (const auto &data : testData) {
        if (data.method == METHOD__FLAT_EARTH_CURVE) {
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

            EXPECT_EQ(rtn, SUCCESS);
            EXPECT_NEAR(data.A_btl__db, result.A_btl__db, ABSTOL_DBL);
            EXPECT_NEAR(data.E_dBuVm, result.E_dBuVm, ABSTOL_DBL);
            EXPECT_NEAR(data.P_rx__dbm, result.P_rx__dbm, ABSTOL_DBL);
            EXPECT_EQ(result.method, data.method);
        }
    }
};

/** Test case to verify LFMF Residue series method results are correct */
TEST_F(TestLFMFPolarizationVertical, ResidueSeriesMethodEquivalentToMatLAB) {
    // Ensure test data was loaded
    EXPECT_NE(static_cast<int>(testData.size()), 0);
    for (const auto &data : testData) {
        if (data.method == METHOD__RESIDUE_SERIES) {
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

            EXPECT_EQ(rtn, SUCCESS);
            EXPECT_NEAR(data.A_btl__db, result.A_btl__db, ABSTOL_DBL);
            EXPECT_NEAR(data.E_dBuVm, result.E_dBuVm, ABSTOL_DBL);
            EXPECT_NEAR(data.P_rx__dbm, result.P_rx__dbm, ABSTOL_DBL);
            EXPECT_EQ(result.method, data.method);
        }
    }
};
