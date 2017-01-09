//
// Created by boruoshihao on 1/8/17.
//

#include "../include/onSiteDensityUpDensityDnOperator.h"
#include "../../../../common/mathHao/include/simple_fun.h"
#include "../../../../common/randomHao/include/random_hao.h"

using namespace std;
using namespace tensor_hao;

OnSiteDensityUpDensityDnOperator::OnSiteDensityUpDensityDnOperator()  { }

OnSiteDensityUpDensityDnOperator::OnSiteDensityUpDensityDnOperator(double dt, const string &decompTypeIn,
                                                                   const TensorHao<double, 1> &U,
                                                                   const TensorHao<double, 1> &mu,
                                                                   const TensorHao<double, 1> &hx,
                                                                   const TensorHao<double, 1> &hy,
                                                                   const TensorHao<double, 1> &hz)
{
    L = U.size();
    decompType = decompTypeIn;
    USum = U.sum();
    setGamma(dt, U);
    setConstDiag(dt, U, mu, hx, hy, hz);
}

OnSiteDensityUpDensityDnOperator::OnSiteDensityUpDensityDnOperator(const OnSiteDensityUpDensityDnOperator &x)
{
    copy_deep(x);
}

OnSiteDensityUpDensityDnOperator::OnSiteDensityUpDensityDnOperator(OnSiteDensityUpDensityDnOperator &&x)
{
    move_deep(x);
}

OnSiteDensityUpDensityDnOperator::~OnSiteDensityUpDensityDnOperator()  { }

OnSiteDensityUpDensityDnOperator &OnSiteDensityUpDensityDnOperator::operator=(const OnSiteDensityUpDensityDnOperator &x)
{
    copy_deep(x);
    return *this;
}

OnSiteDensityUpDensityDnOperator &OnSiteDensityUpDensityDnOperator::operator=(OnSiteDensityUpDensityDnOperator &&x)
{
    move_deep(x);
    return *this;
}

size_t OnSiteDensityUpDensityDnOperator::getL() const { return L; }

const string &OnSiteDensityUpDensityDnOperator::getDecompType() const { return decompType; }

double OnSiteDensityUpDensityDnOperator::getUSum() const { return USum; }

const TensorHao<complex<double>, 1> &OnSiteDensityUpDensityDnOperator::getGamma() const { return gamma; }

const TensorHao<complex<double>, 1> &OnSiteDensityUpDensityDnOperator::getConstDiag00() const { return constDiag00; }

const TensorHao<complex<double>, 1> &OnSiteDensityUpDensityDnOperator::getConstDiag10() const { return constDiag10; }

const TensorHao<complex<double>, 1> &OnSiteDensityUpDensityDnOperator::getConstDiag01() const { return constDiag01; }

const TensorHao<complex<double>, 1> &OnSiteDensityUpDensityDnOperator::getConstDiag11() const { return constDiag11; }

OnSiteDensityUpDensityDnOperatorAux
OnSiteDensityUpDensityDnOperator::sampleAuxFromForce(const OnSiteDensityUpDensityDnOperatorForce &force, double gammaForceCap)
{
    if( L != force.size() ) { cout<<"Error!!! Force size does not consistent with L! "<<force.size()<<endl; exit(1); }

    if( gammaForceCap < 0.0 ) gammaForceCap=0.0;

    OnSiteDensityUpDensityDnOperatorAux field(L);
    double gammaForce, expPlus, expMinus, prob;

    for(size_t i=0; i<L; i++)
    {
        gammaForce = ( gamma(i) * force(i) ).real();
        if( gammaForce > gammaForceCap  ) gammaForce = gammaForceCap;
        if( gammaForce < -gammaForceCap ) gammaForce = -gammaForceCap;

        expMinus = exp( -gammaForce );
        expPlus = exp( gammaForce );
        prob = expMinus / (expMinus + expPlus);

        if( uniformHao() < prob ) field(i) = -1;
        else field(i)=1;
    }

    return field;
}

double OnSiteDensityUpDensityDnOperator::logProbOfAuxFromForce(const OnSiteDensityUpDensityDnOperatorAux &field,
                                                               const OnSiteDensityUpDensityDnOperatorForce &force,
                                                               double gammaForceCap)
{
    if( L != field.size() ) { cout<<"Error!!! Field size does not consistent with L! "<<field.size()<<endl; exit(1); }
    if( L != force.size() ) { cout<<"Error!!! Force size does not consistent with L! "<<force.size()<<endl; exit(1); }

    double logProb(0), gammaForce(0);

    for(size_t i=0; i<L; i++)
    {
        gammaForce = ( gamma(i) * force(i) ).real();
        if( gammaForce > gammaForceCap  ) gammaForce = gammaForceCap;
        if( gammaForce < -gammaForceCap ) gammaForce = -gammaForceCap;

        logProb += field(i) * gammaForce;
    }

    return logProb;
}

void OnSiteDensityUpDensityDnOperator::copy_deep(const OnSiteDensityUpDensityDnOperator &x)
{
    L = x.L;
    decompType = x.decompType;
    USum = x.USum;
    gamma = x.gamma;
    constDiag00 = x.constDiag00;
    constDiag10 = x.constDiag10;
    constDiag01 = x.constDiag01;
    constDiag11 = x.constDiag11;
}
void OnSiteDensityUpDensityDnOperator::move_deep(OnSiteDensityUpDensityDnOperator &x)
{
    L = x.L;
    decompType = x.decompType;
    USum = x.USum;
    gamma = move( x.gamma );
    constDiag00 = move( x.constDiag00 );
    constDiag10 = move( x.constDiag10 );
    constDiag01 = move( x.constDiag01 );
    constDiag11 = move( x.constDiag11 );
}

void OnSiteDensityUpDensityDnOperator::setGamma(double dt, const TensorHao<double,1> &U)
{
    gamma.resize(L);

    if( decompType == "densityCharge" )
    {
        for(size_t i=0; i<L; i++) gamma(i) = solveCoshxEqExpy(-dt * U(i) * 0.5 );
    }
    else if( decompType == "densitySpin" )
    {
        for(size_t i=0; i<L; i++) gamma(i) = solveCoshxEqExpy( dt * U(i) * 0.5 );
    }
    else if( decompType == "hopCharge" )
    {
        for(size_t i=0; i<L; i++) gamma(i) = solveCoshxEqExpy( dt * U(i) * 0.5 );
    }
    else if( decompType == "hopSpin" )
    {
        for(size_t i=0; i<L; i++) gamma(i) = solveCosxEqExpy( dt * U(i) * 0.5 );
    }
    else
    {
        cout<<"Error! Can not find the matched decompType! "<<decompType<<endl;
        exit(1);
    }
}

void OnSiteDensityUpDensityDnOperator::setConstDiag(double dt, const TensorHao<double, 1> &U,
                                                    const TensorHao<double, 1> &mu, const TensorHao<double, 1> &hx,
                                                    const TensorHao<double, 1> &hy, const TensorHao<double, 1> &hz)
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