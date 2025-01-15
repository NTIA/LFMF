/** @file TestWiRoot.cpp
 * Unit tests for WiRoot function.
 */

#include "TestUtils.h"

#include <complex>
#include <stdexcept>

/** Test fixture provides valid inputs for WiRoot */
class TestWiRoot: public ::testing::Test {
        void SetUp() override {
            // Initialize valid inputs
            i = 1;
            q = {1.0, 1.0};
            kind = AiryKind::WONE;
            scaling = AiryScaling::HUFFORD;
        }
    protected:
        std::complex<double> DWi, Wi;
        int i;
        std::complex<double> q;
        AiryKind kind;
        AiryScaling scaling;
        std::complex<double> root;
};

/** Valid test case: AiryKind::WONE */
TEST_F(TestWiRoot, AiryKindWONE) {
    // Test for scaling = HUFFORD
    root = WiRoot(i, DWi, q, Wi, kind, scaling);
    EXPECT_DOUBLE_EQ(root.real(), 1.4829223351194638);
    EXPECT_DOUBLE_EQ(root.imag(), 1.2843356310540217);

    // Test for scaling = WAIT
    root = WiRoot(i, DWi, q, Wi, kind, AiryScaling::WAIT);
    EXPECT_DOUBLE_EQ(root.real(), 0.22646319357739417);
    EXPECT_DOUBLE_EQ(root.imag(), 1.7542471947545168);
}

/** Valid test case: AiryKind::WTWO */
TEST_F(TestWiRoot, AiryKindWTWO) {
    kind = AiryKind::WTWO;
    // Test for scaling = HUFFORD
    root = WiRoot(i, DWi, q, Wi, kind, scaling);
    EXPECT_DOUBLE_EQ(root.real(), 0.22646319357739642);
    EXPECT_DOUBLE_EQ(root.imag(), 1.7542471947545142);

    // Test for scaling = WAIT
    root = WiRoot(i, DWi, q, Wi, kind, AiryScaling::WAIT);
    EXPECT_DOUBLE_EQ(root.real(), 1.482922335119464);
    EXPECT_DOUBLE_EQ(root.imag(), 1.2843356310540215);
}

/** Test a set of conditions that run for small q and small i */
TEST_F(TestWiRoot, SmallQSmallI) {
    // In this case, the root is taken from a const array
    q = {1.0, 1.0};
    i = 1;
    root = WiRoot(i, DWi, q, Wi, kind, scaling);
    EXPECT_DOUBLE_EQ(root.real(), 1.4829223351194638);
    EXPECT_DOUBLE_EQ(root.imag(), 1.2843356310540217);
}

/** Test a set of conditions that run for small q and large i */
TEST_F(TestWiRoot, SmallQLargeI) {
    // In this case, the root is approximated
    q = {1.0, 1.0};
    i = 11;
    root = WiRoot(i, DWi, q, Wi, kind, scaling);
    EXPECT_DOUBLE_EQ(root.real(), 6.7395876387056539);
    EXPECT_DOUBLE_EQ(root.imag(), 11.460104740476151);
}

/** Test a set of conditions that run for large q and small i */
TEST_F(TestWiRoot, LargeQSmallI) {
    // In this case, the root is taken from a const array
    q = {5.0, 5.0};
    i = 1;
    root = WiRoot(i, DWi, q, Wi, kind, scaling);
    EXPECT_DOUBLE_EQ(root.real(), 1.2695003468987784);
    EXPECT_DOUBLE_EQ(root.imag(), 1.9226740699637952);
}
/** Test a set of conditions that run for large q and large i */
TEST_F(TestWiRoot, LargeQLargeI) {
    // In this case, the root is approximated
    q = {5.0, 5.0};
    i = 11;
    root = WiRoot(i, DWi, q, Wi, kind, scaling);
    EXPECT_DOUBLE_EQ(root.real(), 6.9479928400612074);
    EXPECT_DOUBLE_EQ(root.imag(), 11.742393555292688);
}

/** WiRoot should throw an exception when `i` is <= 0 */
TEST_F(TestWiRoot, InvalidRootSelected) {
    i = -1;
    EXPECT_THROW(WiRoot(i, DWi, q, Wi, kind, scaling), std::invalid_argument);
    i = 0;
    EXPECT_THROW(WiRoot(i, DWi, q, Wi, kind, scaling), std::invalid_argument);
}

/** AiryKind::AIRY should throw an exception */
TEST_F(TestWiRoot, AiryKindAIRY) {
    EXPECT_THROW(
        WiRoot(i, DWi, q, Wi, AiryKind::AIRY, scaling), std::invalid_argument
    );
}

/** AiryKind::AIRYD should throw an exception */
TEST_F(TestWiRoot, AiryKindAIRYD) {
    EXPECT_THROW(
        WiRoot(i, DWi, q, Wi, AiryKind::AIRYD, scaling), std::invalid_argument
    );
}

/** AiryKind::BAIRY should throw an exception */
TEST_F(TestWiRoot, AiryKindBAIRY) {
    EXPECT_THROW(
        WiRoot(i, DWi, q, Wi, AiryKind::BAIRY, scaling), std::invalid_argument
    );
}

/** AiryKind::BAIRYD should throw an exception */
TEST_F(TestWiRoot, AiryKindBAIRYD) {
    EXPECT_THROW(
        WiRoot(i, DWi, q, Wi, AiryKind::BAIRYD, scaling), std::invalid_argument
    );
}

/** AiryKind::DWTWO should throw an exception */
TEST_F(TestWiRoot, AiryKindDWTWO) {
    EXPECT_THROW(
        WiRoot(i, DWi, q, Wi, AiryKind::DWTWO, scaling), std::invalid_argument
    );
}

/** AiryKind::DWONE should throw an exception */
TEST_F(TestWiRoot, AiryKindDWONE) {
    EXPECT_THROW(
        WiRoot(i, DWi, q, Wi, AiryKind::DWONE, scaling), std::invalid_argument
    );
}