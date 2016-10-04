//
// Created by boruoshihao on 9/26/16.
//

#include "../include/LanczosBasisWf.h"

using namespace std;
using namespace tensor_hao;

LanczosBasisWf::LanczosBasisWf()
{
}

LanczosBasisWf::LanczosBasisWf(HAO_INT L)
{
    wf = TensorHao<complex<double>, 1>(L);
}

LanczosBasisWf::LanczosBasisWf(const TensorHao<complex<double>, 1> &wf)
{
    LanczosBasisWf::wf = TensorHao<complex<double>, 1>( wf.getRank() );
    copyBlas_cpu( wf, LanczosBasisWf::wf );
}

LanczosBasisWf::LanczosBasisWf(TensorHao<complex<double>, 1> &&wf) : wf( move(wf) )
{
}

LanczosBasisWf::LanczosBasisWf(const LanczosBasisWf &x)
{
    copyDeep(x);
}

LanczosBasisWf::LanczosBasisWf(LanczosBasisWf &&x)
{
    moveDeep(x);
}

LanczosBasisWf& LanczosBasisWf::operator=(const LanczosBasisWf& x)
{
    copyDeep(x);
    return *this;
}

LanczosBasisWf& LanczosBasisWf::operator=(LanczosBasisWf&& x)
{
    moveDeep(x);
    return *this;
}

const tensor_hao::TensorHao<std::complex<double>, 1> &LanczosBasisWf::getWf() const
{
    return wf;
}

void LanczosBasisWf::normalize()
{
    complex<double> inverseNorm = 1.0 / normBlas_cpu(wf);
    scalBlas_cpu(inverseNorm, wf);
}

complex<double> LanczosBasisWf::calculateOverlapWith(const LanczosBasisWf &wfRight) const
{
    return dotcBlas_cpu(wf, wfRight.wf);
}

void LanczosBasisWf::orthogonalizeWith(const LanczosBasisWf &wfBase)
{
    complex<double> minusOverlap = -wfBase.calculateOverlapWith(*this);
    axpyBlas_cpu(minusOverlap, wfBase.wf, wf);
}

void LanczosBasisWf::copyDeep(const LanczosBasisWf &x)
{
    if( wf.size() != x.wf.size() )
    {
        wf = TensorHao<complex<double>, 1>(x.wf.size());
    }

    copyBlas_cpu( x.wf, wf );
}

void LanczosBasisWf::moveDeep(LanczosBasisWf &x)
{
    wf = move(x.wf);
}
