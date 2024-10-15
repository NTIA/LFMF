#include "LFMF.h"

complex<double> wofz(complex<double> z) 
{
 
//     ALGORITHM 680, COLLECTED ALGORITHMS FROM ACM.
//     THIS WORK PUBLISHED IN TRANSACTIONS ON MATHEMATICAL SOFTWARE,
//     VOL. 16, NO. 1, PP. 47.
//
// GIVEN A COMPLEX NUMBER Z = (XI,YI), THIS SUBROUTINE COMPUTES
// THE VALUE OF THE FADDEEVA-FUNCTION W(Z) = EXP(-Z**2)*ERFC(-I*Z),
// WHERE ERF%IS THE COMPLEX COMPLEMENTARY ERROR-FUNCTION AND I
// MEANS SQRT(-1).
// THE ACCURACY OF THE ALGORITHM FOR Z IN THE 1ST AND 2ND QUADRANT
// IS 14 SIGNIFICANT DIGITS; IN THE 3RD AND 4TH IT IS 13 SIGNIFICANT
// DIGITS OUTSIDE A CIRCULAR REGION WITH RADIUS 0.126 AROUND A ZERO
// OF THE FUNCTION.
// ALL REAL VARIABLES IN THE PROGRAM ARE DOUBLE PRECISION.
//
//
// THE CODE CONTAINS A FEW COMPILER-DEPENDENT PARAMETERS :
//    RMAXREAL = THE MAXIMUM VALUE OF RMAXREAL EQUALS THE ROOT OF
//               RMAX = THE LARGEST NUMBER WHICH CAN STILL BE
//               IMPLEMENTED ON THE COMPUTER IN DOUBLE PRECISION
//               FLOATING-POINT ARITHMETIC
//    RMAXEXP  = LN(RMAX) - LN(2)
//    RMAXGONI = THE LARGEST POSSIBLE ARGUMENT OF A DOUBLE PRECISION
//               GONIOMETRI%FUNCTION (DCOS, DSIN, ...)
// THE REASON WHY THESE PARAMETERS ARE NEEDED AS THEY ARE DEFINED WILL
// BE EXPLAINED IN THE CODE BY MEANS OF COMMENTS
//
// PARAMETER LIST
//    flag   = AN ERROR FLAG INDICATING WHETHER OVERFLOW WILL
//             OCCUR OR NOT; TYPE LOGICAL;
//             THE VALUES OF THIS VARIABLE HAVE THE FOLLOWING
//             MEANING :
//             FLAG=.FALSE. : NO ERROR CONDITION
//             FLAG=.TRUE.  : OVERFLOW WILL OCCUR, THE ROUTINE
//                            BECOMES INACTIVE
//
// FURTHERMORE THE PARAMETER FACTOR EQUALS 2/SQRT(PI)
//
// THE ROUTINE IS NOT UNDERFLOW-PROTECTED BUT ANY VARIABLE CAN BE
// PUT TO 0 UPON UNDERFLOW;
//
// REFERENCE - GPM POPPE, CMJ WIJERS; MORE EFFICIENT COMPUTATION OF
// THE COMPLEX ERROR-FUNCTION, ACM TRANS. MATH. SOFTWARE.
//
// Translated from FORTRAN to C/C++ by I. Stevanovic OFCOM CH

 
double FACTOR   = 1.12837916709551257388;
double RMAXREAL = 0.5E+154;
double RMAXEXP  = 708.503061461606E0;
double RMAXGONI = 3.53711887601422E+15;

double XI = z.real();
double YI = z.imag();
 
double XABS = abs(XI);
double YABS = abs(YI);
double X    = XABS/6.3;
double Y    = YABS/4.4;
 
bool flag = false;
 
complex<double> w;
 
double XSUM, YSUM, U, V, XAUX, U1, V1, DAUX, U2, V2, H, H2, KAPN;
double QLAMBDA, RX, RY, TX, TY, SX, SY, W1, CC;
 
int NU, NP1;

//    THE FOLLOWING IF-STATEMENT PROTECTS
//    QRHO = (X**2 + Y**2) AGAINST OVERFLOW
 
if ((XABS > RMAXREAL) || (YABS > RMAXREAL)) {
    flag = true;
    w = complex<double>(0.0,0.0);
    return w;
}
 
double QRHO = X*X + Y*Y;
 
double XABSQ = pow(XABS,2.0);
double XQUAD = XABSQ - pow(YABS, 2.0);
double YQUAD = 2*XABS*YABS;
 
bool A     = (QRHO < 0.085264E0);
 
if (A) {
    
    // IF (QRHO < 0.085264) THEN THE FADDEEVA-FUNCTION IS EVALUATED
    // USING A POWER-SERIES (ABRAMOWITZ/STEGUN, EQUATION (7.1.5), P.297)
    // N IS THE MINIMUM NUMBER OF TERMS NEEDED TO OBTAIN THE REQUIRED
    // ACCURACY
    
    QRHO  = (1-0.85*Y)*sqrt(QRHO);
    int N     = (int)(6 + 72*QRHO);
    int J     = 2*N+1;
    XSUM  = 1.0/J;
    YSUM  = 0.0;
    for (int I = N; I > 0; I--) {
        
        J    = J - 2;
        XAUX = (XSUM*XQUAD - YSUM*YQUAD)/I;
        YSUM = (XSUM*YQUAD + YSUM*XQUAD)/I;
        XSUM = XAUX + 1.0/J;
    }
    U1   = -FACTOR*(XSUM*YABS + YSUM*XABS) + 1.0;
    V1   =  FACTOR*(XSUM*XABS - YSUM*YABS);
    DAUX =  exp(-XQUAD);
    U2   =  DAUX*cos(YQUAD);
    V2   = -DAUX*sin(YQUAD);
    
    U    = U1*U2 - V1*V2;
    V    = U1*V2 + V1*U2;
    
} else {
    
    // IF (QRHO > 1.O) THEN W(Z) IS EVALUATED USING THE LAPLACE
    // CONTINUED FRACTION
    // NU IS THE MINIMUM NUMBER OF TERMS NEEDED TO OBTAIN THE REQUIRED
    // ACCURACY
    
    // IF ((QRHO > 0.085264).AND.(QRHO < 1.0)) THEN W(Z) IS EVALUATED
    // BY A TRUNCATED TAYLOR EXPANSION, WHERE THE LAPLACE CONTINUED FRACTION
    // IS USED TO CALCULATE THE DERIVATIVES OF W(Z)
    // KAPN IS THE MINIMUM NUMBER OF TERMS IN THE TAYLOR EXPANSION NEEDED
    // TO OBTAIN THE REQUIRED ACCURACY
    // NU IS THE MINIMUM NUMBER OF TERMS OF THE CONTINUED FRACTION NEEDED
    // TO CALCULATE THE DERIVATIVES WITH THE REQUIRED ACCURACY
    
    
    if (QRHO > 1.0) {
        H    = 0.0;
        KAPN = 0;
        QRHO = sqrt(QRHO);
        NU   = (int)(3 + (1442/(26*QRHO+77)));
    } else {
        QRHO = (1-Y)*sqrt(1-QRHO);
        H    = 1.88*QRHO;
        H2   = 2*H;
        KAPN = (int)(7  + 34*QRHO);
        NU   = (int)(16 + 26*QRHO);
    }
    
    bool B = (H > 0.0);
    
    if (B) {
        QLAMBDA = pow(H2, KAPN);
    }
    
    RX = 0.0;
    RY = 0.0;
    SX = 0.0;
    SY = 0.0;
    
    for (int N = NU; N>= 0; N--){ 
        NP1 = N + 1;
        TX  = YABS + H + NP1*RX;
        TY  = XABS - NP1*RY;
        CC   = 0.5/(TX*TX + TY*TY);
        RX  = CC*TX;
        RY  = CC*TY;
        if ((B) && (N <= KAPN)) {
            TX = QLAMBDA + SX;
            SX = RX*TX - RY*SY;
            SY = RY*TX + RX*SY;
            QLAMBDA = QLAMBDA/H2;
        }
    }
    
    if (H  == 0.0) {
        U = FACTOR*RX;
        V = FACTOR*RY;
    }else{
        U = FACTOR*SX;
        V = FACTOR*SY;
    }
    
    if (YABS == 0.0){
        U = exp(-XABS*XABS);
    }
}

// EVALUATION OF W(Z) IN THE OTHER QUADRANTS
 
 
if (YI < 0.0) {
    
    if (A) {
        U2    = 2*U2;
        V2    = 2*V2;
    } else {
        XQUAD =  -XQUAD;
        
        
        //        THE FOLLOWING IF-STATEMENT PROTECTS 2*EXP(-Z**2)
        //        AGAINST OVERFLOW
        
        if ((YQUAD > RMAXGONI) || (XQUAD > RMAXEXP)) {
            flag = true;
            w = complex<double>(0.0, 0.0);
            return w;
        }
        
        
        W1 =  2*exp(XQUAD);
        U2  =  W1*cos(YQUAD);
        V2  = -W1*sin(YQUAD);
    }
    
    U = U2 - U;
    V = V2 - V;
    if (XI > 0.0) {
        V = -V;
    }
    
} else {
    if (XI < 0.0){
        V = -V;
    }
}
 
w = complex<double>(U, V);
return w;
 
}
