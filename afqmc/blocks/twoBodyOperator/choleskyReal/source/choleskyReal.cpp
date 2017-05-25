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

CholeskyRealAux CholeskyReal::sampleAuxFromForce(const CholeskyRealForce &force, double cap) const
{
    if( choleskyNumber != force.size() ) { cout<<"Error!!! Force size does not consistent with choleskyNumber! "<<force.size()<<endl; exit(1); }

    CholeskyRealAux choleskyRealAux( choleskyNumber );
    double realSqrtMinusDtForce;
    for(size_t i = 0; i < choleskyNumber; ++i)
    {
        realSqrtMinusDtForce = ( sqrtMinusDt * force(i) ).real();
        if( realSqrtMinusDtForce > cap  ) realSqrtMinusDtForce = cap;
        if( realSqrtMinusDtForce < -cap ) realSqrtMinusDtForce = -cap;

        choleskyRealAux(i) = gaussianHao() + realSqrtMinusDtForce;
    }

    return choleskyRealAux;
}

double CholeskyReal::logOfAuxFromForce(const CholeskyRealAux &aux, const CholeskyRealForce &force, double cap) const
{
    if( choleskyNumber != aux.size() ) { cout<<"Error!!! Aux size does not consistent with choleskyNumber! "<<aux.size()<<endl; exit(1); }
    if( choleskyNumber != force.size() ) { cout<<"Error!!! Force size does not consistent with choleskyNumber! "<<force.size()<<endl; exit(1); }

    // Product: 1/sqrt(2.0*Pi) * Exp( -x^2 / 2.0 ) * Exp( sqrt(-dt) x*force )
    double logProb(0); double aux2Sum(0.0); double auxSqrtMinusDtForce(0.0);
    double realSqrtMinusDtForce;
    for(size_t i = 0; i < choleskyNumber; ++i)
    {
        realSqrtMinusDtForce = ( sqrtMinusDt * force(i) ).real();
        if( realSqrtMinusDtForce > cap  ) realSqrtMinusDtForce = cap;
        if( realSqrtMinusDtForce < -cap ) realSqrtMinusDtForce = -cap;

        auxSqrtMinusDtForce += aux(i)*realSqrtMinusDtForce;
        aux2Sum += aux(i)*aux(i);
    }

    logProb = -0.5*log(2.0*pi)*choleskyNumber - 0.5*aux2Sum + auxSqrtMinusDtForce;
    return logProb;
}


double CholeskyReal::sumOfAuxFromForce(const CholeskyRealForce &force, double cap) const
{
    if( choleskyNumber != force.size() ) { cout<<"Error!!! Force size does not consistent with choleskyNumber! "<<force.size()<<endl; exit(1); }

    double logSum(0.0);
    double realSqrtMinusDtForce;
    for(size_t i = 0; i < choleskyNumber; ++i)
    {
        realSqrtMinusDtForce = ( sqrtMinusDt * force(i) ).real();
        if( realSqrtMinusDtForce > cap  ) realSqrtMinusDtForce = cap;
        if( realSqrtMinusDtForce < -cap ) realSqrtMinusDtForce = -cap;

        logSum += realSqrtMinusDtForce*realSqrtMinusDtForce;
    }
    logSum *= 0.5;

    return exp(logSum);
}

CholeskyRealSample CholeskyReal::getTwoBodySampleFromAux(const CholeskyRealAux &aux) const
{
    if( choleskyNumber != aux.size() ) { cout<<"Error!!! Aux size does not consistent with choleskyNumber! "<<aux.size()<<endl; exit(1); }

    CholeskyRealSample choleskyRealSample(choleskyNumber);

    // Product: 1/sqrt(2.0*Pi) * Exp( -x^2 / 2.0 ) * Exp( -sqrt(-dt) x*B )
    double aux2Sum(0.0); for(size_t i = 0; i < choleskyNumber; ++i) aux2Sum += aux(i)*aux(i);
    double auxBSum(0.0); for(size_t i = 0; i < choleskyNumber; ++i) auxBSum += aux(i) * choleskyBg->operator()(i);
    choleskyRealSample.logw = -0.5*log(2.0*pi)*choleskyNumber - 0.5*aux2Sum - sqrtMinusDt*auxBSum;

    // Add: aux * choleskyVecs
    size_t L = choleskyVecs->rank(0); size_t L2 = L*L;
    TensorHao<double, 1> vecsAux(L2);
    TensorHaoRef<double, 2> vecs(L2, choleskyNumber);
    vecs.point( const_cast<double*>( choleskyVecs->data() ) );
    BL_NAME(gemv)(vecs, aux, vecsAux);

    // sqrt(-dt) * aux * choleskyVecs
    complex<double> *pMatrix = choleskyRealSample.matrix.data();
    const double *pVecsAux = vecsAux.data();
    for(size_t i = 0; i < L2; ++i) pMatrix[i] = sqrtMinusDt * pVecsAux[i];

    return choleskyRealSample;
}

void CholeskyReal::copy_deep(const CholeskyReal &x)
{
    dt = x.dt;
    choleskyVecs = x.choleskyVecs;
    choleskyBg = x.choleskyBg;
    choleskyNumber = x.choleskyNumber;
    sqrtMinusDt = x.sqrtMinusDt;
}