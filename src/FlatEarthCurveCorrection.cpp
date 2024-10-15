#include "LFMF.h"

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
 |                a_e__km       - Effective earth radius, in km
 |
 |      Returns:  E_gw          - Normalized field strength in mV/m
 |
 *===========================================================================*/
double FlatEarthCurveCorrection(complex<double> Delta, complex<double> q, double h_1__km, double h_2__km, double d__km, double k, double a_e__km)
{
    complex<double> j = complex<double>(0.0, 1.0);

    // In order for the wofz() function to be used both here and in gwfe()
    // the argument, qi, has to be defined correctly. The following is how
    // it is done in the original GWFEC.FOR 
    complex<double> qi = (-0.5 + j * 0.5)*sqrt(k*d__km)*Delta;
    complex<double> p = qi * qi;

    complex<double> p2 = pow(p, 2);
    complex<double> q3 = pow(q, 3);
    complex<double> q6 = pow(q, 6);
    complex<double> q9 = pow(q, 9);
 
    complex<double> fofx;
 
    if(abs(q) > 0.1){
        // Find F(p) Eqn (32) NTIA Report 99-368
        complex<double> Fofp = 1.0 + sqrt(PI)*j*qi*wofz(qi);

        // Calculate f(x) which is the normalized electric field, E_ratio; Eqn (31) NTIA Report 99-368
        fofx = Fofp + (1.0 - j * sqrt(PI * p) - (1.0 + 2.0 * p) * Fofp) / (4.0 * q3);
        fofx = fofx + (1.0 - j * sqrt(PI * p) * (1.0 - p) - 2.0 * p + 5.0 * p2 / 6.0 + (p2 / 2.0 - 1.0) * Fofp) / (4.0 * q6);
    } else {
     
        complex<double> A[10];
 
        // [Deminco, Eq 30]
        A[0] = 1.0;
        A[1] = -j * sqrt(PI);
        A[2] = -2.0;
        A[3] = j * sqrt(PI) * (1.0 + 1.0/(4.0*q3));
        A[4] = 4.0/3.0 * ( 1.0 + 1.0/(2.0*q3) );
        A[5] = -j * sqrt(PI) / 4.0 * (1.0 + 3.0 / (4.0 * q3));
        A[6] = -8.0/15.0 * ( 1.0 + 1.0/q3 + 7.0 / (32.0 * q6) );
        A[7] = j * sqrt(PI) / 6.0 * ( 1.0 + 5.0/(4.0*q3) + 27.0 /( 32.0*q6 ) );
        A[8] = 16.0/105.0 * ( 1.0 + 3.0/(2.0*q3) + 27.0/(32.0*q6) );
        A[9] = -j * sqrt(PI)/24.0 * (1.0 + 7.0/ (4.0*q3) + 5.0/(4.0*q6) + 21.0/(64.0*q9));
 
        double x = d__km / a_e__km * pow(k * a_e__km/2.0, (1.0/3.0));
         
        fofx = 0.0 + j*0.0;
 
        // [Deminco, Eq 28]
        for (int ii = 0; ii<10; ii++) {
            fofx = fofx + A[ii] * pow( exp(j * PI/4.0) * q * pow(x,1.0/2.0), ii);
        }
        
        
    }


    // Now find the final normalized field strength from f(x) and the height-gain function for each antenna
    // A height-gain function for an antenna is expressed as two terms of a Taylor series 
    // (See DeMinco NTIA Report 99-368 Aug 1999
    // "Medium Frequency Propagation Prediction Techniques and 
    // Antenna Modeling for Intelligent Transportation Systems (ITS) Broadcast Applications"
    // Equation 36) 

    double E_gw__mVm = abs(fofx*(1.0 + j * k*h_2__km*Delta)*(1.0 + j * k*h_1__km*Delta));

    return E_gw__mVm;
};
