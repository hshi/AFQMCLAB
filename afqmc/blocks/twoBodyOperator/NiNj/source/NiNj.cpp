//
// Created by boruoshihao on 12/30/16.
//

#include "../include/NiNj.h"
#include "../../../../../common/mathHao/include/simple_fun.h"
#include "../../../../../common/randomHao/include/random_hao.h"

using namespace std;
using namespace tensor_hao;

NiNj::NiNj():L(0) { }

NiNj::NiNj(size_t L, const string &decompType,
                                               const TensorHao<OneNiNj,1>& op)
    : L(L), decompType(decompType), op(op)
{
    setGamma();
}

NiNj::NiNj(const NiNj &x) { copy_deep(x); }

NiNj::NiNj(NiNj &&x) { move_deep(x); }

NiNj::~NiNj() { }

NiNj &NiNj::operator=(const NiNj &x) { copy_deep(x); return *this; }

NiNj &NiNj::operator=(NiNj &&x) { move_deep(x); return *this; }

size_t NiNj::getL() const { return L; }

const string &NiNj::getDecompType() const { return decompType; }

const TensorHao<OneNiNj, 1> &NiNj::getOp() const { return op; }

const TensorHao<complex<double>, 1> &NiNj::getGamma() const { return gamma; }

NiNjAux NiNj::sampleAuxFromForce(const NiNjForce &force, double gammaForceCap)
{
    if( gammaForceCap < 0.0 ) gammaForceCap=0.0;

    size_t opSize = op.size();
    NiNjAux field(opSize);
    double gammaForce, expPlus, expMinus, prob;

    for(size_t i=0; i<opSize; i++)
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

void NiNj::copy_deep(const NiNj &x)
{
    L = x.L;
    decompType = x.decompType;
    op = x.op;
    gamma = x.gamma;
}

void NiNj::move_deep(NiNj &x)
{
    L = x.L;
    decompType = x.decompType;
    op = move( x.op );
    gamma = move( x.gamma );
}

void NiNj::setGamma()
{
    size_t opSize = op.size();

    gamma.resize( opSize );
    if(  decompType == "densityCharge" )
    {
        for(size_t i=0; i<opSize; i++) gamma(i) = solveCoshxEqExpy( op(i).V / 2.0 );
    }
    else if( decompType == "densitySpin" )
    {
        for(size_t i=0; i<opSize; i++) gamma(i) = solveCoshxEqExpy(-op(i).V / 2.0 );
    }
    else if( decompType == "hopCharge" )
    {
        for(size_t i=0; i<opSize; i++) gamma(i) = solveCoshxEqExpy(-op(i).V / 2.0 );
    }
    else if( decompType == "hopSpin" )
    {
        for(size_t i=0; i<opSize; i++) gamma(i) = solveCosxEqExpy(-op(i).V / 2.0 );
    }
    else
    {
        cout<<"Error! Can not find the matched decompType! "<<decompType<<endl;
        exit(1);
    }
}