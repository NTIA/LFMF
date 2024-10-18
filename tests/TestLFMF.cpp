#include "LFMFGTest.h"


/*=============================================================================
 |
 |  Description:  The purpose of this is to ensure that CMAKE compiles
 |                the P.676 model DLL correctly.
 |                Test Data is stored in CSV format.
 |
 *===========================================================================*/
class TestLFMF : public ::testing::Test {
protected:
    void SetUp() override {
        // Load test data from CSV
        testData = ReadP676SlantPathInputsAndResult(fileName);
    }

    // Vector to hold test data
    std::vector<SlantPathInputsAndResult> testData;

    double TOLERANCE = 1.0e-10;
    string fileName = "P676SlantPathAttenuationTest_001.csv";
};

/*=============================================================================
 |
 |  Description:  Test case to verify P676 Slant Path Attenuation results are correct
 |
 *===========================================================================*/
TEST_F(TestLFMF, TestLFMFSuccess) {
    // Ensure test data was loaded
    EXPECT_NE(static_cast<int>(testData.size()), 0);
    std::cout << "TestP676 from '" << fileName << "': " << testData.size() << " Test instances." << std::endl;
    for (const auto& data : testData) {
        SlantPathAttenuationResult result;

        int rtn = SlantPathAttenuation(data.f__ghz, data.h_1__km, data.h_2__km, data.beta_1__rad,
            data.atmosphere, &result);

        EXPECT_EQ(rtn, data.expectedReturn);
        EXPECT_NEAR(result.A_gas__db, data.expectedResult.A_gas__db, TOLERANCE);
        EXPECT_NEAR(result.bending__rad, data.expectedResult.bending__rad, TOLERANCE);
        EXPECT_NEAR(result.a__km, data.expectedResult.a__km, TOLERANCE);
        EXPECT_NEAR(result.incident__rad, data.expectedResult.incident__rad, TOLERANCE);
        EXPECT_NEAR(result.delta_L__km, data.expectedResult.delta_L__km, TOLERANCE);
    }
}
