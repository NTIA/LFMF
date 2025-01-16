/** @file TestAiry.cpp
 * Unit tests for the Airy function.
 */

#include "TestUtils.h"

#include <cmath>      // for cos, sin, sqrt
#include <stdexcept>  // for std::invalid_argument

constexpr double AIRY_TOL = 1.0e-4;

/** Test fixture provides valid inputs for Airy */
class TestAiry: public ::testing::Test {
    protected:
        void SetUp() override {
            // Initialize valid inputs
            Z = {8.0, 8.0};  // Evaluated with asymptotic solution
            kind = AiryKind::AIRY;
            scaling = AiryScaling::NONE;
        }
        // input variables
        std::complex<double> Z;
        AiryKind kind;
        AiryScaling scaling;
        // variables to use for comparisons
        std::complex<double> expected;
        std::complex<double> scale_factor;  // to translate HUFFORD/WAIT
        // output variable
        std::complex<double> airy;
};

/** Exercise the function for AiryKind::AIRY with all scaling options */
TEST_F(TestAiry, AsymptoticAIRY) {
    // Scaling does not apply to AiryKind::AIRY
    expected = {6.57693e-07, 9.31233e-06};

    airy = Airy(Z, kind, scaling);
    EXPECT_NEAR(airy.real(), expected.real(), AIRY_TOL);
    EXPECT_NEAR(airy.imag(), expected.imag(), AIRY_TOL);

    scaling = AiryScaling::HUFFORD;
    airy = Airy(Z, kind, scaling);
    EXPECT_NEAR(airy.real(), expected.real(), AIRY_TOL);
    EXPECT_NEAR(airy.imag(), expected.imag(), AIRY_TOL);

    scaling = AiryScaling::WAIT;
    airy = Airy(Z, kind, scaling);
    EXPECT_NEAR(airy.real(), expected.real(), AIRY_TOL);
    EXPECT_NEAR(airy.imag(), expected.imag(), AIRY_TOL);
}

/** Exercise the function for AiryKind::AIRYD with all scaling options */
TEST_F(TestAiry, AsymptoticAIRYD) {
    // Scaling does not apply to AiryKind::AIRYD
    expected = {9.79016e-06, -2.99217e-05};
    kind = AiryKind::AIRYD;

    airy = Airy(Z, kind, scaling);
    EXPECT_NEAR(airy.real(), expected.real(), AIRY_TOL);
    EXPECT_NEAR(airy.imag(), expected.imag(), AIRY_TOL);

    scaling = AiryScaling::HUFFORD;
    airy = Airy(Z, kind, scaling);
    EXPECT_NEAR(airy.real(), expected.real(), AIRY_TOL);
    EXPECT_NEAR(airy.imag(), expected.imag(), AIRY_TOL);

    scaling = AiryScaling::WAIT;
    airy = Airy(Z, kind, scaling);
    EXPECT_NEAR(airy.real(), expected.real(), AIRY_TOL);
    EXPECT_NEAR(airy.imag(), expected.imag(), AIRY_TOL);
}

/** Exercise the function for AiryKind::BAIRY with all scaling options */
TEST_F(TestAiry, AsymptoticBAIRY) {
    expected = {-1605.15434, -4807.19999};
    kind = AiryKind::BAIRY;
    // Scaling does not apply to AiryKind::BAIRY

    airy = Airy(Z, kind, scaling);
    EXPECT_NEAR(airy.real(), expected.real(), AIRY_TOL);
    EXPECT_NEAR(airy.imag(), expected.imag(), AIRY_TOL);

    scaling = AiryScaling::HUFFORD;
    airy = Airy(Z, kind, scaling);
    EXPECT_NEAR(airy.real(), expected.real(), AIRY_TOL);
    EXPECT_NEAR(airy.imag(), expected.imag(), AIRY_TOL);

    scaling = AiryScaling::WAIT;
    airy = Airy(Z, kind, scaling);
    EXPECT_NEAR(airy.real(), expected.real(), AIRY_TOL);
    EXPECT_NEAR(airy.imag(), expected.imag(), AIRY_TOL);
}

/** Exercise the function for AiryKind::BAIRYD with all scaling options */
TEST_F(TestAiry, AsymptoticBAIRYD) {
    expected = {1301.23297, -16955.98329};
    kind = AiryKind::BAIRYD;
    // Scaling does not apply to AiryKind::BAIRYD

    airy = Airy(Z, kind, scaling);
    EXPECT_NEAR(airy.real(), expected.real(), AIRY_TOL);
    EXPECT_NEAR(airy.imag(), expected.imag(), AIRY_TOL);

    scaling = AiryScaling::HUFFORD;
    airy = Airy(Z, kind, scaling);
    EXPECT_NEAR(airy.real(), expected.real(), AIRY_TOL);
    EXPECT_NEAR(airy.imag(), expected.imag(), AIRY_TOL);

    scaling = AiryScaling::WAIT;
    airy = Airy(Z, kind, scaling);
    EXPECT_NEAR(airy.real(), expected.real(), AIRY_TOL);
    EXPECT_NEAR(airy.imag(), expected.imag(), AIRY_TOL);
}

/** Exercise the function for AiryKind::WONE with all scaling options */
TEST_F(TestAiry, AsymptoticWONE) {
    // Expected values with HUFFORD scaling
    expected = {-4807.19999, 1605.15435};
    scale_factor = {0.0, std::sqrt(PI)};  // translates to WAIT
    kind = AiryKind::WONE;

    // WONE with scaling NONE is invalid

    scaling = AiryScaling::HUFFORD;
    airy = Airy(Z, kind, scaling);
    EXPECT_NEAR(airy.real(), expected.real(), AIRY_TOL);
    EXPECT_NEAR(airy.imag(), expected.imag(), AIRY_TOL);

    scaling = AiryScaling::WAIT;
    airy = Airy(Z, kind, scaling);
    EXPECT_NEAR(airy.real(), (expected * scale_factor).real(), 1.0e-3);
    EXPECT_NEAR(airy.imag(), (expected * scale_factor).imag(), 1.0e-3);
}

/** Exercise the function for AiryKind::DWONE with all scaling options */
TEST_F(TestAiry, AsymptoticDWONE) {
    // Expected values with HUFFORD scaling
    expected = {-16955.983274, -1301.233026};
    scale_factor = {0.0, std::sqrt(PI)};  // translates to WAIT
    kind = AiryKind::DWONE;

    // DWONE with scaling NONE is invalid

    scaling = AiryScaling::HUFFORD;
    airy = Airy(Z, kind, scaling);
    EXPECT_NEAR(airy.real(), expected.real(), AIRY_TOL);
    EXPECT_NEAR(airy.imag(), expected.imag(), AIRY_TOL);

    scaling = AiryScaling::WAIT;
    airy = Airy(Z, kind, scaling);
    EXPECT_NEAR(airy.real(), (expected * scale_factor).real(), 1.0e-3);
    EXPECT_NEAR(airy.imag(), (expected * scale_factor).imag(), 1.0e-3);
}

/** Exercise the function for AiryKind::WTWO with all scaling options */
TEST_F(TestAiry, AsymptoticWTWO) {
    // Expected values with HUFFORD scaling
    expected = {4807.19999, -1605.15435};  // translates to WAIT
    // Scaling factor to translate expected result
    scale_factor = {0.0, -std::sqrt(PI)};
    kind = AiryKind::WTWO;

    // WTWO with scaling NONE is invalid

    scaling = AiryScaling::HUFFORD;
    airy = Airy(Z, kind, scaling);
    EXPECT_NEAR(airy.real(), expected.real(), AIRY_TOL);
    EXPECT_NEAR(airy.imag(), expected.imag(), AIRY_TOL);

    scaling = AiryScaling::WAIT;
    airy = Airy(Z, kind, scaling);
    EXPECT_NEAR(airy.real(), (expected * scale_factor).real(), 1.0e-3);
    EXPECT_NEAR(airy.imag(), (expected * scale_factor).imag(), 1.0e-3);
}

/** Exercise the function for AiryKind::DWTWO with all scaling options */
TEST_F(TestAiry, AsymptoticDWTWO) {
    // Expected values with HUFFORD scaling
    expected = {16955.983313, 1301.232906};
    scale_factor = {0.0, -std::sqrt(PI)};  // translates to WAIT
    kind = AiryKind::DWTWO;

    // DWTWO with scaling NONE is invalid

    scaling = AiryScaling::HUFFORD;
    airy = Airy(Z, kind, scaling);
    EXPECT_NEAR(airy.real(), expected.real(), AIRY_TOL);
    EXPECT_NEAR(airy.imag(), expected.imag(), AIRY_TOL);

    scaling = AiryScaling::WAIT;
    airy = Airy(Z, kind, scaling);
    EXPECT_NEAR(airy.real(), (expected * scale_factor).real(), 1.0e-3);
    EXPECT_NEAR(airy.imag(), (expected * scale_factor).imag(), 1.0e-3);
}

/** Ensure Hufford's Airy functions of the third kind meet their definitions */
TEST_F(TestAiry, TestThirdKindDefinition) {
    std::complex<double> j(0, 1.0);
    std::complex<double> wi, ai, bi;
    scaling = AiryScaling::HUFFORD;

    // Test that Wi(1)(z) = Ai(z) - j*Bi(z)
    wi = Airy(Z, AiryKind::WONE, scaling);
    ai = Airy(Z, AiryKind::AIRY, AiryScaling::NONE);
    bi = Airy(Z, AiryKind::BAIRY, AiryScaling::NONE);
    expected = ai - j * bi;  // -4807.2, 1605.15
    EXPECT_NEAR(wi.real(), expected.real(), 1.0e-5);
    EXPECT_NEAR(wi.imag(), expected.imag(), 1.0e-5);

    // Test that Wi(2)(z) = Ai(z) + j*Bi(z)
    wi = Airy(Z, AiryKind::WTWO, scaling);
    expected = ai + j * bi;  // 4807.2, -1605.15
    EXPECT_NEAR(wi.real(), expected.real(), 1.0e-5);
    EXPECT_NEAR(wi.imag(), expected.imag(), 1.0e-5);
}

/** Invalid `scaling` input throws an exception */
TEST_F(TestAiry, InvalidScaling) {
    scaling = static_cast<AiryScaling>(-1);
    EXPECT_THROW(Airy(Z, kind, scaling), std::invalid_argument);

    // Scaling NONE is invalid with Airy functions of the third kind
    scaling = AiryScaling::NONE;
    kind = AiryKind::WONE;
    EXPECT_THROW(Airy(Z, kind, scaling), std::invalid_argument);
    kind = AiryKind::WTWO;
    EXPECT_THROW(Airy(Z, kind, scaling), std::invalid_argument);
    kind = AiryKind::DWONE;
    EXPECT_THROW(Airy(Z, kind, scaling), std::invalid_argument);
    kind = AiryKind::DWTWO;
    EXPECT_THROW(Airy(Z, kind, scaling), std::invalid_argument);
}
