//
// Created by boruoshihao on 5/23/17.
//

#include "../include/choleskyReal.h"
#include "../../../../../common/common.h"

using namespace std;
using namespace tensor_hao;

#define pi 3.14159265358979324

CholeskyReal::CholeskyReal():dt(0), choleskyVecs(nullptr), choleskyBg(nullptr) { }

CholeskyReal::CholeskyReal(double dt,
                           const TensorHao<double, 3> &choleskyVecs,
                           const TensorHao<double, 1> &choleskyBg)
{
    CholeskyReal::dt = dt;
    CholeskyReal::choleskyVecs = &choleskyVecs;
    CholeskyReal::choleskyBg = &choleskyBg;

    choleskyNumber = choleskyVecs.rank(2);
    sqrtMinusDt = sqrt( -dt*complex<double>(1.0, 0.0) );
}

CholeskyReal::CholeskyReal(const CholeskyReal &x) { copy_deep(x); }

CholeskyReal::~CholeskyReal() { }

CholeskyReal &CholeskyReal::operator=(const CholeskyReal &x) { copy_deep(x); return *this; }

double CholeskyReal::getDt() const { return dt; }

const TensorHao<double, 3> *CholeskyReal::getCholeskyVecs() const { return choleskyVecs; }

const TensorHao<double, 1> *CholeskyReal::getCholeskyBg() const { return choleskyBg; }

size_t CholeskyReal::getCholeskyNumber() const { return choleskyNumber; }

const complex<double> &CholeskyReal::getSqrtMinusDt() const { return sqrtMinusDt; }

size_t CholeskyReal::returnBasisSize() const { return choleskyVecs->rank(0); }

CholeskyRealAux CholeskyReal::sampleAuxFromForce(const CholeskyRealForce &force) const
{
    if( choleskyNumber != force.size() ) { cout<<"Error!!! Force size does not consistent with choleskyNumber! "<<force.size()<<endl; exit(1); }

    CholeskyRealAux choleskyRealAux( choleskyNumber );
    for(size_t i = 0; i < choleskyNumber; ++i)  choleskyRealAux(i) = gaussianHao() + force(i);

    return choleskyRealAux;
}

double CholeskyReal::logProbOfAuxFromForce(const CholeskyRealAux &aux, const CholeskyRealForce &force) const
{
    if( choleskyNumber != aux.size() ) { cout<<"Error!!! Aux size does not consistent with choleskyNumber! "<<aux.size()<<endl; exit(1); }
    if( choleskyNumber != force.size() ) { cout<<"Error!!! Force size does not consistent with choleskyNumber! "<<force.size()<<endl; exit(1); }

    // Product: 1/sqrt(2.0*Pi) * Exp( -(x-force)^2 / 2.0 )
    double logProb(0); double auxMinusForceSquare(0); double tmp;
    for(size_t i = 0; i < choleskyNumber; ++i)
    {
        tmp = aux(i)-force(i);
        auxMinusForceSquare += tmp*tmp;
    }
    logProb = -0.5*log(2.0*pi)*choleskyNumber - 0.5*auxMinusForceSquare;

    return logProb;
}

CholeskyRealSample CholeskyReal::getTwoBodySampleFromAux(const CholeskyRealAux &aux) const
{
    if( choleskyNumber != aux.size() ) { cout<<"Error!!! Aux size does not consistent with choleskyNumber! "<<aux.size()<<endl; exit(1); }

    CholeskyRealSample choleskyRealSample( choleskyVecs->rank(0) );

    // Product: 1/sqrt(2.0*Pi) * Exp( -x^2 / 2.0 ) * Exp( -sqrt(-dt) x*B )
    double aux2Sum(0.0); double auxBSum(0.0);
    for(size_t i = 0; i < choleskyNumber; ++i)
    {
        aux2Sum += aux(i)*aux(i);
        auxBSum += aux(i) * choleskyBg->operator()(i);
    }
    choleskyRealSample.logw = -0.5*log(2.0*pi)*choleskyNumber - 0.5*aux2Sum - sqrtMinusDt*auxBSum;

    setTwoBodySampleMatrix(choleskyRealSample, aux);

    return choleskyRealSample;
}

CholeskyRealSample CholeskyReal::getTwoBodySampleFromAuxForce(const CholeskyRealAux &aux, const CholeskyRealForce &force) const
{
    if( choleskyNumber != aux.size() ) { cout<<"Error!!! Aux size does not consistent with choleskyNumber! "<<aux.size()<<endl; exit(1); }
    if( choleskyNumber != force.size() ) { cout<<"Error!!! Force size does not consistent with choleskyNumber! "<<force.size()<<endl; exit(1); }

    CholeskyRealSample choleskyRealSample( choleskyVecs->rank(0) );

    // Product: Exp( force^2/2 - x*force ) Exp( -sqrt(-dt) x*B )
    double force2Sum(0.0); double auxForce(0.0); double auxBSum(0.0);
    for(size_t i = 0; i < choleskyNumber; ++i)
    {
        force2Sum += force(i)*force(i);
        auxForce += aux(i)*force(i);
        auxBSum += aux(i) * choleskyBg->operator()(i);
    }
    choleskyRealSample.logw =  0.5*force2Sum - auxForce - sqrtMinusDt*auxBSum;

    setTwoBodySampleMatrix(choleskyRealSample, aux);

    return choleskyRealSample;
}

double CholeskyReal::getMemory() const
{
    return 8.0*3.0+8.0+16.0;
}

void CholeskyReal::copy_deep(const CholeskyReal &x)
{
    dt = x.dt;
    choleskyVecs = x.choleskyVecs;
    choleskyBg = x.choleskyBg;
    choleskyNumber = x.choleskyNumber;
    sqrtMinusDt = x.sqrtMinusDt;
}

void CholeskyReal::setTwoBodySampleMatrix(CholeskyRealSample &choleskyRealSample, const CholeskyRealAux &aux) const
{
    //Calculate aux * choleskyVecs
    size_t L = choleskyVecs->rank(0); size_t L2 = L*L;
    TensorHao<double, 1> vecsAux(L2);
    TensorHaoRef<double, 2> vecs(L2, choleskyNumber);
    vecs.point( const_cast<double*>( choleskyVecs->data() ) );
    BL_NAME(gemv)(vecs, aux, vecsAux);

    // sqrt(-dt) * aux * choleskyVecs
    complex<double> *pMatrix = choleskyRealSample.matrix.data();
    const double *pVecsAux = vecsAux.data();
    for(size_t i = 0; i < L2; ++i) pMatrix[i] = sqrtMinusDt * pVecsAux[i];
}