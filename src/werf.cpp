#include "..\include\LFMF.h"

/*=============================================================================
 |
 |  Description:  Calculates the complex error function, which is more 
 |                commonly known as the Faddeeva function (a.k.a. w(z) in 
 |                Abramowitz and Stegun Eqn 7.1.3). This routine makes the 
 |                calculation in the first quadrant then transforms to the 
 |                appropriate quadrant indicated by the input parameter, qi.
 |                For large argument the asymptotic form of w(z) is used 
 |                while for small argument it is solved by using the
 |                Maclaurin series expansion of the Dawson's integral is used.
 |
 |        Input:  qi    - Input argument
 |
 |      Outputs:  [None]
 |
 |      Returns:  w     - Complex value of w(qi) ( exp(-qi^2)*erfc(-i*qi) )
 |
 *===========================================================================*/
complex<double> werf(complex<double> qi) 
{
    complex<double> za, a, w, jzn;

    complex<double> j = complex<double>(0.0, 1.0);

    // Force qi into the first quadrant
    complex<double> z = complex<double>(abs(qi.real()), abs(qi.imag()));

    if (abs(qi) > 2.0) 
    {
        complex<double> zsq = pow(z, 2);

        // ref:
        //  - https://dlmf.nist.gov/7.9
        //  - https://arxiv.org/ftp/arxiv/papers/1711/1711.05291.pdf
        w = z * ((0.4613135279 * j) / (zsq - 0.1901635092) + (0.09999216168 * j) / (zsq - 1.7844927485) + (0.0028838938748 * j) / (zsq - 5.52534374379));
    }
    else 
    {
        // Determine the Faddeeva function, w(z), using the method given in 
        // "Computation of the Complex Error Function" J.A.C. Weideman
        // SAIM Vol 31, No. 5, pp 1497-1518, October 1994
        // from Eqn (4) in the above:
        // w(z) = ... = exp(-x^2) + ((i*2)/sqrt(PI))*daw(x)
        complex<double> term = z;
        double num = 1.0;
        double denom = 1.0;
        double sign = 1.0;
        complex<double> Csum = z;

        // Determine the Maclaurin series of the Dawson's integral
        for (int i = 1; i < WERF_TERMS; i++) {
            term = term * z * z;                // z^(2n+1)
            num = num * 2;                      // 2^n
            denom = denom * (2 * i + 1);        // (2n+1)!!
            sign = -sign;                       // (-1)^n
            Csum = Csum + sign * (num / denom) * term;
        }

        // Given Csum is series expansion of the Dawson's integral 
        // find the Faddeeva function from: 
        // w(z) = ... = exp(-x^2) + ((2*i)/sqrt(PI))*daw(x)
        w = exp(-1.0 * z * z) + ((2.0 * j) / sqrt(PI)) * Csum;
    };

    // Now put the result in the correct quadrant given by qi
    if (qi.imag() < 0.0) 
    {
        // Use 7.1.11 w(-z) = 2*exp(-z^2) - w(z) 
        // If you are in the lower half plane
        w = 2.0 * exp(-1.0 * z * z) - w;
        if (qi.real() > 0.0)
            w = conj(w);
    }
    else 
    {
        if (qi.real() < 0.0)
            w = conj(w);
    };

    return w;
};