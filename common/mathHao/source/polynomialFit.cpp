//
// Created by boruoshihao on 4/28/17.
//

#include "../include/polynomialFit.h"

using namespace std;
using namespace tensor_hao;

PolynomialFit::PolynomialFit(const TensorHao<double, 1> &x_in, const TensorHao<double, 1> &y_in, size_t polynomialOrder_in)
{
    x = &x_in;
    y = &y_in;
    polynomialOrder = polynomialOrder_in;

    analysis();

    coefficient.resize(polynomialOrder+1);
    if( polynomialOrder == 0 ) coefficient(0) = y_in.mean();
    if( polynomialOrder == 1 ) fitLinearFunction();
    else fitBySolvingLinearEquation();
}

const TensorHao<double, 1> &PolynomialFit::getCoefficient() const
{
    return coefficient;
}

const tensor_hao::TensorHao<double, 1> PolynomialFit::returnFittedY() const
{
    size_t vectorSize = x->size();
    TensorHao<double,1> fittedY(vectorSize);

    for(size_t i = 0; i < vectorSize; ++i)
    {
        fittedY(i) = 0.0;
        for(size_t j = 0; j < polynomialOrder+1; ++j)
        {
            fittedY(i) += coefficient(j) * pow( x->operator()(i), j );
        }
    }

    return fittedY;
}

void PolynomialFit::analysis() const
{
    if( x->size() != y->size() ) { cout<<"Error!!! Size is not consistent for x and y vector!"<<endl; exit(1); }
    if( polynomialOrder >= x->size() ) { cout<<"Warning!!! Polynomial order is larger equal than vectorSize!"<<endl; }
}

void PolynomialFit::fitLinearFunction()
{
    size_t vectorSize = x->size();

    double xMean = x->mean();
    double yMean = y->mean();
    double Sxy = ( (*x)*(*y) ).sum() - xMean*yMean*vectorSize;
    double Sxx = ( (*x)*(*x) ).sum() - xMean*xMean*vectorSize;
    coefficient(1) = Sxy/Sxx;
    coefficient(0) = yMean - coefficient(1)*xMean;
}

void PolynomialFit::fitBySolvingLinearEquation()
{
    size_t vectorSize = x->size();

    TensorHao<double, 1> sumPowerX(2*polynomialOrder+1);
    for(size_t i=0; i<2*polynomialOrder+1; i++)
    {
        sumPowerX(i)=0;
        for(size_t j=0;j<vectorSize;j++) sumPowerX(i) += pow( x->operator()(j),i );
    }

    TensorHao<double, 2> sumPowXY(polynomialOrder+1, 1);
    for(size_t i=0;i<polynomialOrder+1;i++)
    {
        sumPowXY(i, 0)=0;
        for(size_t j=0;j<vectorSize;j++)
        {
            sumPowXY(i, 0) += pow( x->operator()(j),i ) * y->operator()(j);
        }
    }

    TensorHao<double, 2> polynomialMatrix( polynomialOrder+1, polynomialOrder+1 );
    for(size_t i=0; i<polynomialOrder+1;i++)
    {
        for(size_t j=0; j<polynomialOrder+1;j++)  polynomialMatrix(j, i) = sumPowerX(i+j);
    }

    TensorHao<double, 2> coefficient2D = solve_lineq_cpu( LUconstruct_cpu( move(polynomialMatrix) ), move( sumPowXY ) );

    for(size_t i = 0; i < polynomialOrder+1; ++i) coefficient(i) = coefficient2D(i,0);
}