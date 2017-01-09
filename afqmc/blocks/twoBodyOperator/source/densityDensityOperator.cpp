//
// Created by boruoshihao on 12/30/16.
//

#include "../include/densityDensityOperator.h"
#include "../../../../common/mathHao/include/simple_fun.h"
#include "../../../../common/randomHao/include/random_hao.h"

using namespace std;
using namespace tensor_hao;

DensityDensityOperator::DensityDensityOperator():L(0) { }

DensityDensityOperator::DensityDensityOperator(size_t L, const string &decompType,
                                               const TensorHao<OneDensityDensityOperator,1>& op)
    : L(L), decompType(decompType), op(op)
{
    setGamma();
}

DensityDensityOperator::DensityDensityOperator(const DensityDensityOperator &x) { copy_deep(x); }

DensityDensityOperator::DensityDensityOperator(DensityDensityOperator &&x) { move_deep(x); }

DensityDensityOperator::~DensityDensityOperator() { }

DensityDensityOperator &DensityDensityOperator::operator=(const DensityDensityOperator &x) { copy_deep(x); return *this; }

DensityDensityOperator &DensityDensityOperator::operator=(DensityDensityOperator &&x) { move_deep(x); return *this; }

size_t DensityDensityOperator::getL() const { return L; }

const string &DensityDensityOperator::getDecompType() const { return decompType; }

const TensorHao<OneDensityDensityOperator, 1> &DensityDensityOperator::getOp() const { return op; }

const TensorHao<complex<double>, 1> &DensityDensityOperator::getGamma() const { return gamma; }

DensityDensityOperatorAux DensityDensityOperator::sampleAuxFromForce(const DensityDensityOperatorForce &force, double gammaForceCap)
{
    if( gammaForceCap < 0.0 ) gammaForceCap=0.0;

    size_t opSize = op.size();
    DensityDensityOperatorAux field(opSize);
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

void DensityDensityOperator::copy_deep(const DensityDensityOperator &x)
{
    L = x.L;
    decompType = x.decompType;
    op = x.op;
    gamma = x.gamma;
}

void DensityDensityOperator::move_deep(DensityDensityOperator &x)
{
    L = x.L;
    decompType = x.decompType;
    op = move( x.op );
    gamma = move( x.gamma );
}

void DensityDensityOperator::setGamma()
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