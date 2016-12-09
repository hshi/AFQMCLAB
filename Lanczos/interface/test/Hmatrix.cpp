//
// Created by boruoshihao on 12/8/16.
//

#include "Hmatrix.h"

using namespace std;
using namespace tensor_hao;

const TensorHao<complex<double>, 2> & Hmatrix::getHm() const
{
    return Hm;
}

void Hmatrix::resize(size_t L)
{
    Hm.resize(L, L);
    randomFill(Hm);
    auto HmDagger = conjtrans(Hm);
    Hm += HmDagger;
    checkHermitian(Hm);
}

size_t Hmatrix::getWfSize() const
{
    return Hm.rank(0);
};

void Hmatrix::applyHToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew) const
{
    if( wfNew.size() != wf.size() ) wfNew.resize( wf.size() );
    gemv_cpu( Hm, wf.getWf(), wfNew.wfRef() );
};

void Hmatrix::projectSymmetry(LanczosBasisWf &wf) const
{
};