//
// Created by boruoshihao on 9/26/16.
//

#include <fstream>
#include "../include/LanczosBasisWf.h"

using namespace std;
using namespace tensor_hao;

LanczosBasisWf::LanczosBasisWf()
{
}

LanczosBasisWf::LanczosBasisWf(size_t L)
{
    wf = TensorHao<complex<double>, 1>(L);
}

LanczosBasisWf::LanczosBasisWf(const TensorHao<complex<double>, 1> &wf)
{
    LanczosBasisWf::wf = TensorHao<complex<double>, 1>( wf.getRank() );
    copy_cpu(wf, LanczosBasisWf::wf);
}

LanczosBasisWf::LanczosBasisWf(TensorHao<complex<double>, 1> &&wf) : wf( move(wf) )
{
}

LanczosBasisWf::LanczosBasisWf(const LanczosBasisWf &x)
{
    copyDeep(x.wf);
}

LanczosBasisWf::LanczosBasisWf(LanczosBasisWf &&x)
{
    moveDeep(x.wf);
}

LanczosBasisWf& LanczosBasisWf::operator=(const TensorHao<complex<double>, 1> &wf)
{
    copyDeep(wf);
    return *this;
}

LanczosBasisWf& LanczosBasisWf::operator=(TensorHao<complex<double>, 1> &&wf)
{
    moveDeep(wf);
    return *this;
}

LanczosBasisWf &LanczosBasisWf::operator=(std::complex<double> x)
{
    size_t wfSize = wf.size();

#pragma omp parallel for
    for(size_t i = 0; i < wfSize; ++i)
    {
        wf(i) = x;
    }
    return *this;
}

LanczosBasisWf& LanczosBasisWf::operator=(const LanczosBasisWf& x)
{
    copyDeep(x.wf);
    return *this;
}

LanczosBasisWf& LanczosBasisWf::operator=(LanczosBasisWf&& x)
{
    moveDeep(x.wf);
    return *this;
}

const tensor_hao::TensorHao<std::complex<double>, 1> &LanczosBasisWf::getWf() const
{
    return wf;
}

tensor_hao::TensorHao<std::complex<double>, 1> &LanczosBasisWf::wfRef()
{
    return wf;
}

size_t LanczosBasisWf::size() const
{
    return wf.size();
}

void LanczosBasisWf::resize(size_t L)
{
    wf.resize(L);
}

void LanczosBasisWf::randomFill()
{
    tensor_hao::randomFill(wf);
}

void LanczosBasisWf::scale(std::complex<double> alpha)
{
    scal_cpu(alpha, wf);
}

void LanczosBasisWf::addEqual(complex<double> alpha, const LanczosBasisWf &wfAdd)
{
    axpy_cpu(alpha, wfAdd.wf, wf);
}

complex<double> LanczosBasisWf::calculateOverlapWith(const LanczosBasisWf &wfRight) const
{
    return dotc_cpu(wf, wfRight.wf);
}


void LanczosBasisWf::orthogonalizeWith(const LanczosBasisWf &wfBase)
{
    complex<double> minusOverlap = -wfBase.calculateOverlapWith(*this);
    addEqual(minusOverlap, wfBase);
}

double LanczosBasisWf::normalize()
{
    double EuclideanNorm = nrm2_cpu(wf);
    complex<double> alpha = 1.0 / EuclideanNorm;
    scale(alpha);
    return EuclideanNorm;
}

void LanczosBasisWf::orthonormalizeWith(const LanczosBasisWf &wfBase)
{
    orthogonalizeWith(wfBase);
    normalize();
}

void LanczosBasisWf::read(const std::string& filename)
{
    wf.read(filename);
}

void LanczosBasisWf::write(const std::string& filename) const
{
    wf.write(filename);
}

void LanczosBasisWf::copyDeep(const TensorHao<complex<double>, 1> &wf)
{
    if( LanczosBasisWf::wf.size() != wf.size() )
    {
        LanczosBasisWf::wf = TensorHao<complex<double>, 1>( wf.size() );
    }
    copy_cpu(wf, LanczosBasisWf::wf);
}

void LanczosBasisWf::moveDeep(TensorHao<complex<double>, 1> &wf)
{
    LanczosBasisWf::wf = move(wf);
}