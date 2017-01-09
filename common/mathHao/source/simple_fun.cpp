#include "../include/simple_fun.h"
using namespace std;

/******************************************************/
/*solve the equation cosh(x)=exp(y), input y, return x*/
/******************************************************/
complex<double> solveCoshxEqExpy(double y)
{
    complex<double> ey={exp(y),0};
    complex<double> gamma=log(ey-sqrt(ey*ey-1.0));

    //Since gamma is pure real or pure imaginary, set it:
    if( abs( gamma.real() ) < abs( gamma.imag() ) )  gamma=complex<double>( 0, gamma.imag() );
    else                                             gamma=complex<double>( gamma.real(), 0 );

    return gamma;
}


/******************************************************/
/*solve the equation cos(x)=exp(y), input y, return x*/
/******************************************************/
complex<double> solveCosxEqExpy(double y)
{
    complex<double> ey={exp(y),0};
    complex<double> gamma=acos(ey);

    //Since gamma is pure real or pure imaginary, set it:
    if( abs( gamma.real() ) < abs( gamma.imag() ) )  gamma=complex<double>( 0, gamma.imag() );
    else                                             gamma=complex<double>( gamma.real(), 0 );

    return gamma;
}


/***************************************************************/
/* Input matrix is:                                            */
/* (a , c*)                                                    */
/* (c , b )                                                    */
/* Output exp of this matrix                                   */
/* Similiar to diagonalize BCS matrix, see my note for details */
/***************************************************************/
void exp2by2Matrix(double &a, double &b, complex<double> &c)
{
    if( std::abs(c) < 1e-60 )
    {
        a = exp(a); b = exp(b); c = 0.0;
        return;
    }

    double abs_c = std::abs(c);
    double arg_c = std::arg(c);

    double d0, d1;
    complex<double> v00, v01, v10, v11;
    complex<double> im(0.0,1.0);

    if( std::abs(a-b) < 1e-60 )
    {
        double norm = 1.0/sqrt(2.0);

        //Exp of Eigenvalues
        d0 = exp( -abs_c + a ); 
        d1 = exp(  abs_c + b );

        //Eigenvectors
        v00 = -norm;
        v10 =  norm * exp( im*arg_c );
        v01 =  norm;
        v11 =  norm * exp( im*arg_c );
    }
    else
    {
        double xi    = 0.5*atan( 2.0*abs_c/(a-b) );

        //Exp of Eigenvalues
        d0 =exp(  0.5*cos(2.0*xi)*(a-b) + sin(2.0*xi)*abs_c + (a+b)*0.5 );
        d1 =exp( -0.5*cos(2.0*xi)*(a-b) - sin(2.0*xi)*abs_c + (a+b)*0.5 );

        //Eigenvectors
        v00 =  exp(-im*arg_c*0.5 ) * cos(xi);
        v10 =  exp( im*arg_c*0.5 ) * sin(xi);
        v01 = -exp(-im*arg_c*0.5 ) * sin(xi);
        v11 =  exp( im*arg_c*0.5 ) * cos(xi);
    }

    //Calculate v.d.v^{+}
    a = ( d0*v00*conj(v00) + d1*v01*conj(v01) ).real();
    b = ( d0*v10*conj(v10) + d1*v11*conj(v11) ).real();
    c = d0*v10*conj(v00) + d1*v11*conj(v01);
}


/***************************************************************/
/* Input matrix is:                                            */
/* (a , c*)                                                    */
/* (c , b )                                                    */
/* Output eigenvalues and eigenvectors                         */
/***************************************************************/
void eigen2by2Matrix(double a, double b, complex<double> c, double *eigvalue, complex<double> *eigvec)
{
    if( std::abs(c) < 1e-60 )
    {
        eigvalue[0] = a; eigvalue[1] = b;
        eigvec[0] = 1.0; eigvec[1] = 0.0; eigvec[2] = 0.0; eigvec[3] = 1.0;
        return; 
    }

    double abs_c = std::abs(c);
    double arg_c = std::arg(c);
    complex<double> im(0.0,1.0);

    if( std::abs(a-b) < 1e-60 )
    {
        double norm = 1.0/sqrt(2.0);

        eigvalue[0] = -abs_c + a; eigvalue[1] = abs_c + b;
        eigvec[0] = -norm; eigvec[1] =  norm * exp( im*arg_c ); eigvec[2] =  norm;  eigvec[3] =  norm * exp( im*arg_c );
    }
    else
    {
        double xi    = 0.5*atan( 2.0*abs_c/(a-b) );

        //Eigenvalues
        eigvalue[0] = 0.5*cos(2.0*xi)*(a-b) + sin(2.0*xi)*abs_c + (a+b)*0.5;
        eigvalue[1] =-0.5*cos(2.0*xi)*(a-b) - sin(2.0*xi)*abs_c + (a+b)*0.5;

        //Eigenvectors
        eigvec[0] =  exp(-im*arg_c*0.5 ) * cos(xi);
        eigvec[1] =  exp( im*arg_c*0.5 ) * sin(xi);
        eigvec[2] = -exp(-im*arg_c*0.5 ) * sin(xi);
        eigvec[3] =  exp( im*arg_c*0.5 ) * cos(xi);
    }
}

size_t binomialCoeff(size_t n, size_t k)
{
    if( k > n ) { cout<<"Error!!! k should be small or equal than n!"<<endl; exit(1); }

    vector<size_t> C(k+1, 0); C[0] = 1;
    for (size_t i = 1; i <= n; i++)
    {
        for (size_t j = min(i, k); j > 0; j--) C[j] += C[j-1];
    }
    return C[k];
}