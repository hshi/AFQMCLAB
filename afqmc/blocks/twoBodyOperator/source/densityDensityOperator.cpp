//
// Created by boruoshihao on 12/30/16.
//

#include "../include/densityDensityOperator.h"

using namespace std;
using namespace tensor_hao;

DensityDensityOperator::DensityDensityOperator() { }

DensityDensityOperator::DensityDensityOperator(size_t L, const TensorHao<OneDensityDensityOperator,1>& op,
                                               const string &decompType): L(L), op(op), decompType(decompType)
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

const TensorHao<OneDensityDensityOperator, 1> &DensityDensityOperator::getGamma() const { return gamma; }

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
    gamma.resize( op.size() );


}
