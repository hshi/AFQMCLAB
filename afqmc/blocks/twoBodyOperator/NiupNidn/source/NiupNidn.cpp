//
// Created by boruoshihao on 1/8/17.
//
#include "../../../../../common/common.h"
#include "../include/NiupNidn.h"

using namespace std;
using namespace tensor_hao;

NiupNidn::NiupNidn()  { }

NiupNidn::NiupNidn(double dt,
                   const string &decompTypeIn,
                   const TensorHao<double, 1> &U,
                   const TensorHao<double, 1> &mu,
                   const TensorHao<double, 1> &hx,
                   const TensorHao<double, 1> &hy,
                   const TensorHao<double, 1> &hz)
{
    L = U.size();
    decompType = decompTypeIn;
    dtUSum = dt*U.sum();
    dtU = dt * U;
    setGamma();
    setConstDiag(dt, U, mu, hx, hy, hz);
}

NiupNidn::NiupNidn(const NiupNidn &x) { copy_deep(x); }

NiupNidn::NiupNidn(NiupNidn &&x) { move_deep(x); }

NiupNidn::~NiupNidn()  { }

NiupNidn &NiupNidn::operator=(const NiupNidn &x) { copy_deep(x); return *this; }

NiupNidn &NiupNidn::operator=(NiupNidn &&x) { move_deep(x); return *this; }

size_t NiupNidn::getL() const { return L; }

const string &NiupNidn::getDecompType() const { return decompType; }

double NiupNidn::getDtUSum() const { return dtUSum; }

const TensorHao<double, 1> &NiupNidn::getDtU() const { return dtU; }

const TensorHao<complex<double>, 1> &NiupNidn::getGamma() const { return gamma; }

const TensorHao<complex<double>, 1> &NiupNidn::getConstDiag00() const { return constDiag00; }

const TensorHao<complex<double>, 1> &NiupNidn::getConstDiag10() const { return constDiag10; }

const TensorHao<complex<double>, 1> &NiupNidn::getConstDiag01() const { return constDiag01; }

const TensorHao<complex<double>, 1> &NiupNidn::getConstDiag11() const { return constDiag11; }

NiupNidnForce NiupNidn::readForce(const std::string &filename) const
{
    NiupNidnForce force(L);

    if( !checkFile(filename) ) force = 0.0;
    else readFile( force.size(), force.data(), filename );

    return force;
}

NiupNidnAux NiupNidn::sampleAuxFromForce(const NiupNidnForce &force) const
{
    if( L != force.size() ) { cout<<"Error!!! Force size does not consistent with L! "<<force.size()<<endl; exit(1); }

    NiupNidnAux aux(L);
    double expPlus, expMinus, prob;

    for(size_t i=0; i<L; i++)
    {
        expMinus = exp( -force(i) );
        expPlus = exp( force(i) );
        prob = expMinus / (expMinus + expPlus);

        if( uniformHao() < prob ) aux(i) = -1;
        else aux(i)=1;
    }

    return aux;
}

double NiupNidn::logProbOfAuxFromForce(const NiupNidnAux &aux, const NiupNidnForce &force) const
{
    if( L != aux.size() ) { cout<<"Error!!! Aux size does not consistent with L! "<<aux.size()<<endl; exit(1); }
    if( L != force.size() ) { cout<<"Error!!! Force size does not consistent with L! "<<force.size()<<endl; exit(1); }

    double logProb(0);
    for(size_t i=0; i<L; i++)
    {
        logProb += aux(i)*force(i) - log( exp(force(i)) + exp(-force(i)) );
    }

    return logProb;
}

NiupNidnSample NiupNidn::getTwoBodySampleFromAux(const NiupNidnAux &aux) const
{
    if( L != aux.size() ) { cout<<"Error!!! Aux size does not consistent with L! "<<aux.size()<<endl; exit(1); }

    NiupNidnSample twoBodySample(L);

    setTwoBodySampleMatrix(twoBodySample, aux);
    
    if( decompType == "densityCharge" )
    {
        KahanData<complex<double>> gammaAuxSum;
        for(size_t i = 0; i < L; ++i) gammaAuxSum += aux(i)*1.0*gamma(i);
        twoBodySample.logw = log(0.5)*L + dtUSum*0.5 - gammaAuxSum.returnSum();
    }
    else if( decompType == "densitySpin" )
    {
        twoBodySample.logw = log(0.5)*L;
    }
    else if( decompType == "hopCharge" )
    {
        twoBodySample.logw = log(0.5)*L;
    }
    else if( decompType == "hopSpin" )
    {
        twoBodySample.logw = log(0.5)*L;
    }
    else
    {
        cout<<"Error! Can not find the matched decompType! "<<decompType<<endl;
        exit(1);
    }

    return twoBodySample;
}

NiupNidnSample NiupNidn::getTwoBodySampleFromAuxForce(const NiupNidnAux &aux, const NiupNidnForce &force) const
{
    NiupNidnSample twoBodySample = getTwoBodySampleFromAux(aux);
    
    twoBodySample.logw = twoBodySample.logw - logProbOfAuxFromForce(aux, force);
    
    return twoBodySample;
}

size_t NiupNidn::getAuxSize() const
{
    return L;
}

size_t NiupNidn::getAuxDiffSize(const NiupNidnAux &auxOne, const NiupNidnAux &auxTwo) const
{
    if( auxOne.size() != auxTwo.size() ) { cout<<"Error!!! size is not consistent between auxOne and auxTwo!"<<endl; exit(1); }
    if( auxOne.size() != L ) { cout<<"Error!!! size of auxOne is not L!"<<endl; exit(1); }

    size_t diffSize(0);
    for(size_t i = 0; i < L; ++i)
    {
        if( auxOne(i) != auxTwo(i) ) diffSize++;
    }
    return diffSize;
}

double NiupNidn::getMemory() const
{
    double mem(0.0);
    mem += 8.0+8.0;
    mem += dtU.getMemory();
    mem += gamma.getMemory();
    mem += constDiag00.getMemory();
    mem += constDiag10.getMemory();
    mem += constDiag01.getMemory();
    mem += constDiag11.getMemory();
    return mem;
}

void NiupNidn::copy_deep(const NiupNidn &x)
{
    L = x.L;
    decompType = x.decompType;
    dtUSum = x.dtUSum;
    dtU = x.dtU;
    gamma = x.gamma;
    constDiag00 = x.constDiag00;
    constDiag10 = x.constDiag10;
    constDiag01 = x.constDiag01;
    constDiag11 = x.constDiag11;
}

void NiupNidn::move_deep(NiupNidn &x)
{
    L = x.L;
    decompType = x.decompType;
    dtUSum = x.dtUSum;
    dtU = move( x.dtU );
    gamma = move( x.gamma );
    constDiag00 = move( x.constDiag00 );
    constDiag10 = move( x.constDiag10 );
    constDiag01 = move( x.constDiag01 );
    constDiag11 = move( x.constDiag11 );
}

void NiupNidn::setGamma()
{
    gamma.resize(L);

    if( decompType == "densityCharge" )
    {
        for(size_t i=0; i<L; i++) gamma(i) = solveCoshxEqExpy(-dtU(i) * 0.5 );
    }
    else if( decompType == "densitySpin" )
    {
        for(size_t i=0; i<L; i++) gamma(i) = solveCoshxEqExpy( dtU(i) * 0.5 );
    }
    else if( decompType == "hopCharge" )
    {
        for(size_t i=0; i<L; i++) gamma(i) = solveCoshxEqExpy( dtU(i) * 0.5 );
    }
    else if( decompType == "hopSpin" )
    {
        for(size_t i=0; i<L; i++) gamma(i) = solveCosxEqExpy( dtU(i) * 0.5 );
    }
    else
    {
        cout<<"Error! Can not find the matched decompType! "<<decompType<<endl;
        exit(1);
    }
}

void NiupNidn::setConstDiag(double dt,
                            const TensorHao<double, 1> &U,
                            const TensorHao<double, 1> &mu,
                            const TensorHao<double, 1> &hx,
                            const TensorHao<double, 1> &hy,
                            const TensorHao<double, 1> &hz)
{
    constDiag00.resize(L); constDiag01.resize(L);
    constDiag10.resize(L); constDiag11.resize(L);

    double a, b; complex<double> c;
    for(size_t i = 0; i < L; ++i)
    {
        a = -dt * ( U(i)*0.5 - mu(i) + hz(i)*0.5 );
        b = -dt * ( U(i)*0.5 - mu(i) - hz(i)*0.5 );
        c = -dt * 0.5 * complex<double>( hx(i), hy(i) );

        exp2by2Matrix(a,b,c);

        constDiag00(i) = a; constDiag01(i) = conj(c);
        constDiag10(i) = c; constDiag11(i) = b;
    }
}

void NiupNidn::setTwoBodySampleMatrix(NiupNidnSample &twoBodySample, const NiupNidnAux &aux) const
{
    if( decompType == "densityCharge" )
    {
        //  ( exp(gamma x)    0      ) ( constDiag00 constDiag01 )
        //  (    0      exp(gamma x) ) ( constDiag10 constDiag11 )
        complex<double> expGammaAux;
        for(size_t i = 0; i < L; ++i)
        {
            expGammaAux = exp( aux(i)*1.0*gamma(i) );

            twoBodySample.diag00(i) = expGammaAux * constDiag00(i);
            twoBodySample.diag10(i) = expGammaAux * constDiag10(i);
            twoBodySample.diag01(i) = expGammaAux * constDiag01(i);
            twoBodySample.diag11(i) = expGammaAux * constDiag11(i);
        }
    }
    else if( decompType == "densitySpin" )
    {
        //  ( exp(gamma x)       0        ) ( constDiag00 constDiag01 )
        //  (    0          exp(-gamma x) ) ( constDiag10 constDiag11 )
        complex<double> expGammaAux, expMinusGammaAux;
        for(size_t i = 0; i < L; ++i)
        {
            expGammaAux = exp( aux(i)*1.0*gamma(i) );
            expMinusGammaAux = 1.0 / expGammaAux;

            twoBodySample.diag00(i) = expGammaAux * constDiag00(i);
            twoBodySample.diag10(i) = expMinusGammaAux * constDiag10(i);
            twoBodySample.diag01(i) = expGammaAux * constDiag01(i);
            twoBodySample.diag11(i) = expMinusGammaAux * constDiag11(i);
        }
    }
    else if( decompType == "hopCharge" )
    {
        //   (  cosh(gamma x)  sinh(gamma x) )  ( constDiag00 constDiag01 )
        //   (  sinh(gamma x)  cosh(gamma x) )  ( constDiag10 constDiag11 )
        complex<double> coshGammaAux, sinhGammaAux;
        for(size_t i = 0; i < L; ++i)
        {
            coshGammaAux = cosh( aux(i)*1.0*gamma(i) );
            sinhGammaAux = sinh( aux(i)*1.0*gamma(i) );

            twoBodySample.diag00(i) = coshGammaAux * constDiag00(i) + sinhGammaAux * constDiag10(i);
            twoBodySample.diag10(i) = sinhGammaAux * constDiag00(i) + coshGammaAux * constDiag10(i);
            twoBodySample.diag01(i) = coshGammaAux * constDiag01(i) + sinhGammaAux * constDiag11(i);
            twoBodySample.diag11(i) = sinhGammaAux * constDiag01(i) + coshGammaAux * constDiag11(i);
        }
    }
    else if( decompType == "hopSpin" )
    {
        //   (  cos(gamma x) sin(gamma x) ) ( constDiag00 constDiag01 )
        //   ( -sin(gamma x) cos(gamma x) ) ( constDiag10 constDiag11 )
        complex<double> cosGammaAux, sinGammaAux;
        for(size_t i = 0; i < L; ++i)
        {
            cosGammaAux = cos( aux(i)*1.0*gamma(i) );
            sinGammaAux = sin( aux(i)*1.0*gamma(i) );

            twoBodySample.diag00(i) =  cosGammaAux * constDiag00(i) + sinGammaAux * constDiag10(i);
            twoBodySample.diag10(i) = -sinGammaAux * constDiag00(i) + cosGammaAux * constDiag10(i);
            twoBodySample.diag01(i) =  cosGammaAux * constDiag01(i) + sinGammaAux * constDiag11(i);
            twoBodySample.diag11(i) = -sinGammaAux * constDiag01(i) + cosGammaAux * constDiag11(i);
        }
    }
    else
    {
        cout<<"Error! Can not find the matched decompType! "<<decompType<<endl;
        exit(1);
    }
}