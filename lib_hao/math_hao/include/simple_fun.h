#ifndef SIMPLE_FUN_H
#define SIMPLE_FUN_H

#include <iostream>
#include <vector>
#include <complex>
#include <algorithm>
#include <cmath>

/******************************************************/
/*solve the equation cosh(x)=exp(y), input y, return x*/
/******************************************************/
std::complex<double> coshx_eq_expy(double y);

/******************************************************/
/*solve the equation cos(x)=exp(y), input y, return x*/
/******************************************************/
std::complex<double> cosx_eq_expy(double y);


/***************************************************************/
/* Input matrix is:                                            */
/* (a , c*)                                                    */
/* (c , b )                                                    */
/* Output exp of this matrix                                   */
/* Similiar to diagonalize BCS matrix, see my note for details */
/***************************************************************/
void exp_matrix(double& a, double& b, std::complex<double>& c);


/***************************************************************/
/* Input matrix is:                                            */
/* (a , c*)                                                    */
/* (c , b )                                                    */
/* Output eigenvalues and eigenvectors                         */
/***************************************************************/
void eigen_matrix(double a, double b, std::complex<double> c, double* eig, std::complex<double>* vec);

#endif
