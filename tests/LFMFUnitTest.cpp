/** @file LFMFUnitTest.cpp
 * Implements the google tests from ITS.Propagation.LFMF.
 */

#include "LFMFGTest.h"
TEST(LFMFUnitTest, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(LFMFUnitTest, AiryUnit) {
    complex<double> Z = complex<double>(1.1682788835042248, -2.0240843744484041);
    int kind = 7;
    int scaling = 10;
    complex<double> a = Airy(Z, kind, scaling);
    EXPECT_NEAR(a.real(), 0.0026324159896967498, 1e-6);
    EXPECT_NEAR(a.imag(), -0.00070755364700167943, 1e-6);
};

TEST(LFMFUnitTest, wofzUnit) {
    complex<double> qi = complex<double>(-77.535144030507098, 141.91224512225062);
    complex<double> q = wofz(qi);
    EXPECT_NEAR(q.real(), 0.0030616782889356449, 1e-6);
    EXPECT_NEAR(q.imag(), -0.0016727139353032337, 1e-6);
};

TEST(LFMFUnitTest, WiRootUnit) {
    int i = 1;
    complex<double> DWi = complex<double>(0.0, 0.0);
    complex<double> q = complex<double>(-644.31445826967774, -645.31889509633902);
    complex<double> Wi = complex<double>(0.0, 0.0);
    int kind = 7;
    int scaling = 10;
    complex<double> w = WiRoot(i, &DWi, q, &Wi, kind, scaling);
    EXPECT_NEAR(w.real(), 1.1682788835042248, 1e-6);
    EXPECT_NEAR(w.imag(), -2.0240843744484041, 1e-6);
};

TEST(LFMFUnitTest, ResidueSeriesUnit) {
    double d__km = 1000.0000000000000;
    double k = 0.20958450219516817;
    double h_1__km = 0.0000000000000000;
    double h_2__km = 0.0000000000000000;
    double nu = 9.6190110607347474;
    double theta__rad = 0.11774375919975148;
    complex<double> q = complex<double>(-644.31445826967774, -645.31889509633902);

    double r = ResidueSeries(d__km, k, h_1__km, h_2__km, nu, theta__rad, q);
    EXPECT_NEAR(r, 2.4998877307699495e-07, 1e-6);
};

TEST(LFMFUnitTest, FlatEarthCurveCorrectionUnit) {
    complex<double>  Delta = complex<double>(3.9138592723335672, -1.1481700238342050);
    complex<double> q = complex<double>(-111.45734271952689, -379.93358580790789);
    double h_1__km = 0.0015000000000000000;
    double h_2__km = 0.0054999999999999997;
    double d__km = 15.000000000000000;
    double k = 209.58450219516817;
    double a_e__km = 8729.2769375851076;

    double f = FlatEarthCurveCorrection(Delta, q, h_1__km, h_2__km, d__km, k, a_e__km
    );
    EXPECT_NEAR(f, 0.00017063613901238263, 1e-6);
};
