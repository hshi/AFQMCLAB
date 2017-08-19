//
// Created by boruoshihao on 5/23/17.
//
#include "../../../../../common/common.h"
#include "../include/choleskyReal.h"

using namespace std;
using namespace tensor_hao;

#define pi 3.14159265358979324

CholeskyReal::CholeskyReal():dt(0), sqrtMinusDt(0), choleskyNumber(0),choleskyBg(nullptr) { }

CholeskyReal::CholeskyReal(double dt,
                           const TensorHao<double, 3> &choleskyVecs,
                           const TensorHao<double, 1> &choleskyBg)
{
    CholeskyReal::dt = dt;
    sqrtMinusDt = sqrt( -dt*complex<double>(1.0, 0.0) );
    choleskyNumber = choleskyVecs.rank(2);
    initialSqrtMinusDtCholeskyVecs(choleskyVecs);
    CholeskyReal::choleskyBg = &choleskyBg;
}

CholeskyReal::CholeskyReal(const CholeskyReal &x) { copy_deep(x); }

CholeskyReal::CholeskyReal(CholeskyReal &&x) { move_deep(x); }

CholeskyReal::~CholeskyReal() { }

CholeskyReal &CholeskyReal::operator = (const CholeskyReal &x) { copy_deep(x); return *this; }

CholeskyReal &CholeskyReal::operator = (CholeskyReal &&x) { move_deep(x); return *this; }

double CholeskyReal::getDt() const { return dt; }

const TensorHao<complex<double>, 3> &CholeskyReal::getSqrtMinusDtCholeskyVecs() const { return sqrtMinusDtCholeskyVecs; }

const TensorHao<double, 1> *CholeskyReal::getCholeskyBg() const { return choleskyBg; }

size_t CholeskyReal::getCholeskyNumber() const { return choleskyNumber; }

const complex<double> &CholeskyReal::getSqrtMinusDt() const { return sqrtMinusDt; }

size_t CholeskyReal::returnBasisSize() const { return sqrtMinusDtCholeskyVecs.rank(0); }

CholeskyRealForce CholeskyReal::readForce(const std::string &filename) const
{
    CholeskyRealForce force(choleskyNumber);

    if( !checkFile(filename) ) force = 0.0;
    else readFile( force.size(), force.data(), filename );

    return force;
}

CholeskyRealAux CholeskyReal::sampleAuxFromForce(const CholeskyRealForce &force) const
{
    if( choleskyNumber != force.size() ) { cout<<"Error!!! Force size does not consistent with choleskyNumber! "<<force.size()<<endl; exit(1); }

    CholeskyRealAux choleskyRealAux( choleskyNumber );
    for(size_t i = 0; i < choleskyNumber; ++i)  choleskyRealAux(i) = gaussianHao() + force(i);

    return choleskyRealAux;
}

complex<double> CholeskyReal::logProbOfAuxFromForce(const CholeskyRealAux &aux, const CholeskyRealForce &force) const
{
    if( choleskyNumber != aux.size() ) { cout<<"Error!!! Aux size does not consistent with choleskyNumber! "<<aux.size()<<endl; exit(1); }
    if( choleskyNumber != force.size() ) { cout<<"Error!!! Force size does not consistent with choleskyNumber! "<<force.size()<<endl; exit(1); }

    // Product: 1/sqrt(2.0*Pi) * Exp( -(x-force)^2 / 2.0 )
    complex<double> logProb(0,0), auxMinusForceSquare(0,0), tmp;
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

    CholeskyRealSample choleskyRealSample( sqrtMinusDtCholeskyVecs.rank(0) );

    // Product: 1/sqrt(2.0*Pi) * Exp( -x^2 / 2.0 ) * Exp( -sqrt(-dt) x*B )
    complex<double> aux2Sum(0,0), auxBSum(0,0);
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

    CholeskyRealSample choleskyRealSample( sqrtMinusDtCholeskyVecs.rank(0) );

    // Product: Exp( force^2/2 - x*force ) Exp( -sqrt(-dt) x*B )
    complex<double> force2Sum(0,0), auxForce(0,0),auxBSum(0,0);
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
    return 8.0+16.0+8.0+sqrtMinusDtCholeskyVecs.getMemory()+8.0;
}

void CholeskyReal::copy_deep(const CholeskyReal &x)
{
    dt = x.dt;
    sqrtMinusDt = x.sqrtMinusDt;
    choleskyNumber = x.choleskyNumber;
    sqrtMinusDtCholeskyVecs = x.sqrtMinusDtCholeskyVecs;
    choleskyBg = x.choleskyBg;
}

void CholeskyReal::move_deep(CholeskyReal &x)
{
    dt = x.dt;
    sqrtMinusDt = x.sqrtMinusDt;
    choleskyNumber = x.choleskyNumber;
    sqrtMinusDtCholeskyVecs = move( x.sqrtMinusDtCholeskyVecs );
    choleskyBg = x.choleskyBg;
}

void CholeskyReal::initialSqrtMinusDtCholeskyVecs(const tensor_hao::TensorHao<double, 3> &choleskyVecs)
{
    sqrtMinusDtCholeskyVecs.resize( choleskyVecs.getRank() );
    complex<double> *p0 = sqrtMinusDtCholeskyVecs.data();
    const double *p1 = choleskyVecs.data();

    //There is a cubic scaling, can be faster by OpenMP
    size_t choleskyVecsSize = choleskyVecs.size();
    for(size_t i = 0; i < choleskyVecsSize; ++i) p0[i] = p1[i] * sqrtMinusDt;
}

void CholeskyReal::setTwoBodySampleMatrix(CholeskyRealSample &choleskyRealSample, const CholeskyRealAux &aux) const
{
    //Calculate aux * sqrtMinusDt * choleskyVecs
    size_t L = sqrtMinusDtCholeskyVecs.rank(0); size_t L2 = L * L;
    TensorHaoRef<complex<double>, 1> vecsAux(L2);
    TensorHaoRef<complex<double>, 2> vecs(L2, choleskyNumber);
    vecsAux.point( choleskyRealSample.matrix.data() );
    vecs.point( const_cast<complex<double>*> ( sqrtMinusDtCholeskyVecs.data() ) );
    BL_NAME(gemv)(vecs, aux, vecsAux);
}

