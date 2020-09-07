#include "..\include\LFMF.h"

/*=============================================================================
 |
 |  Description:  Calculates the groundwave field strength using the flat Earth
 |                approximation with curvature correction.
 |
 |   References:  99-368 "Medium Frequency Propagation
 |                  Prediction Techniques and Antenna Modeling for
 |                  Intelligent Transportation Systems (ITS) Broadcast 
 |                  Applications", Nicholas DeMinco.  Eq (31)
 |                J. Wait, "Radiation From a Vertical Antenna Over a Curved
 |                  Stratified Ground", Journal of Research of the National 
 |                  Bureau of Standards Vol 56, No. 4, April 1956 
 |                  Research Paper 2671
 |
 |        Input:  Delta         - Surface impedance
 |                q             - Intermediate value -j*nu*delta
 |                h_1__km       - Height of the higher antenna, in km
 |                h_2__km       - Height of the lower antenna, in km
 |                d__km         - Path distance, in km
 |                k             - Wavenumber, in rad/km
 |
 |      Returns:  E_gw          - Normalized field strength in mV/m
 |
 *===========================================================================*/
double FlatEarthCurveCorrection(complex<double> Delta, complex<double> q, double h_1__km, double h_2__km, double d__km, double k)
{
    complex<double> j = complex<double>(0.0, 1.0);

    // In order for the werf() function to be used both here and in gwfe()
    // the argument, qi, has to be defined correctly. The following is how
    // it is done in the original GWFEC.FOR 
    complex<double> qi = (-0.5 + j * 0.5)*sqrt(k*d__km)*Delta;
    complex<double> p = qi * qi;

    complex<double> q3 = pow(q, 3);
    complex<double> q6 = pow(q, 6);

    // Find F(p) Eqn (32) NTIA Report 99-368
    complex<double> Fofp = 1.0 + sqrt(PI)*j*qi*werf(qi);

    // Calculate f(x) which is the normalized electric field, E_ratio; Eqn (31) NTIA Report 99-368
    complex<double> fofx = Fofp + (1.0 - j * sqrt(PI * p) - (1.0 + 2.0 * p) * Fofp) / (4.0 * q3) + (1.0 - j * sqrt(PI * p) * (1.0 - p) - 2.0 * p + 5.0 * p * p / 6.0 + (p * p / 2.0 - 1.0) * Fofp) / (4.0 * q6);

    // Now find the final normalized field strength from f(x) and the height-gain function for each antenna
    // A height-gain function for an antenna is expressed as two terms of a Taylor series 
    // (See DeMinco NTIA Report 99-368 Aug 1999
    // "Medium Frequency Propagation Prediction Techniques and 
    // Antenna Modeling for Intelligent Transportation Systems (ITS) Broadcast Applications"
    // Equation 36) 

    double E_gw__mVm = abs(fofx*(1.0 + j * k*h_2__km*Delta)*(1.0 + j * k*h_1__km*Delta));

    return E_gw__mVm;
};