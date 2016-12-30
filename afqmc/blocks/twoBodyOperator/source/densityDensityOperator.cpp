//
// Created by boruoshihao on 12/30/16.
//

#include "../include/densityDensityOperator.h"

using namespace std;
using namespace tensor_hao;

DensityDensityOperator::DensityDensityOperator() { }

DensityDensityOperator::DensityDensityOperator(size_t L) { op.resize(L); }

DensityDensityOperator::DensityDensityOperator(const DensityDensityOperator &x) { copy_deep(x); }

DensityDensityOperator::DensityDensityOperator(DensityDensityOperator &&x) { move_deep(x); }

DensityDensityOperator::~DensityDensityOperator() { }

DensityDensityOperator &DensityDensityOperator::operator=(const DensityDensityOperator &x) { copy_deep(x); return *this; }

DensityDensityOperator &DensityDensityOperator::operator=(DensityDensityOperator &&x) { move_deep(x); return *this; }

void DensityDensityOperator::copy_deep(const DensityDensityOperator &x)
{
    op = x.op;
}

void DensityDensityOperator::move_deep(DensityDensityOperator &x)
{
    op = move( x.op );
}