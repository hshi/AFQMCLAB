//
// Created by boruoshihao on 12/28/16.
//

#include "../include/hoppingOperator.h"

using namespace std;
using namespace tensor_hao;

HoppingOperator::HoppingOperator():logw(0.0) { }

HoppingOperator::HoppingOperator(size_t L):logw(0.0) { op.resize(L, L); }

HoppingOperator::HoppingOperator(const HoppingOperator &x) { copy_deep(x); }

HoppingOperator::HoppingOperator(HoppingOperator &&x) { move_deep(x); }

HoppingOperator::~HoppingOperator() { }

HoppingOperator &HoppingOperator::operator=(const HoppingOperator &x)  { copy_deep(x); return *this; }

HoppingOperator &HoppingOperator::operator=(HoppingOperator &&x) { move_deep(x); return *this; }

const complex<double> &HoppingOperator::getLogw() const { return logw; }

const TensorHao<complex<double>, 2> &HoppingOperator::getOp() const { return op; }

std::complex<double> &HoppingOperator::logwRef() { return logw; }

tensor_hao::TensorHao<std::complex<double>, 2> &HoppingOperator::opRef() { return op; }

size_t HoppingOperator::getL() const { return op.rank(0); }

void HoppingOperator::copy_deep(const HoppingOperator &x)
{
    logw = x.logw;
    op = x.op;
}

void HoppingOperator::move_deep(HoppingOperator &x)
{
    logw = x.logw;
    op = move( x.op );
}
