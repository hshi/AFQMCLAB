#ifndef AFQMCLAB_SIMPLE_FUN_H
#define AFQMCLAB_SIMPLE_FUN_H

#include <iostream>
#include <vector>
#include <complex>
#include <algorithm>
#include <cmath>

/******************************************************/
/*solve the equation cosh(x)=exp(y), input y, return x*/
/******************************************************/
std::complex<double> solveCoshxEqExpy(double y);

/******************************************************/
/*solve the equation cos(x)=exp(y), input y, return x*/
/******************************************************/
std::complex<double> solveCosxEqExpy(double y);


/***************************************************************/
/* Input matrix is:                                            */
/* (a , c*)                                                    */
/* (c , b )                                                    */
/* Output exp of this matrix                                   */
/* Similiar to diagonalize BCS matrix, see my note for details */
/***************************************************************/
void exp2by2Matrix(double &a, double &b, std::complex<double> &c);


/***************************************************************/
/* Input matrix is:                                            */
/* (a , c*)                                                    */
/* (c , b )                                                    */
/* Output eigenvalues and eigenvectors                         */
/***************************************************************/
void eigen2by2Matrix(double a, double b, std::complex<double> c, double *eigvalue, std::complex<double> *eigvec);

/************************************/
/*Input n, k, Output: Binomial(n, k)*/
/************************************/
size_t binomialCoeff(size_t n, size_t k);

#endif
