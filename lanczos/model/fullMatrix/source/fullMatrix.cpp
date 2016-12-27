//
// Created by boruoshihao on 10/25/16.
//

#include <fstream>
#include "../include/fullMatrix.h"

using namespace std;
using namespace tensor_hao;

FullMatrix::FullMatrix(const TensorHao<complex<double>, 2> &HmIn)
{
    Hm.resize( HmIn.getRank() );
    copy_cpu(HmIn, Hm);
}

FullMatrix::FullMatrix(TensorHao<complex<double>, 2> &&HmIn)
{
    Hm = move( HmIn );
}

FullMatrix::FullMatrix(const std::string &filename)
{
    read(filename);
}

const TensorHao<complex<double>, 2> &FullMatrix::getHm() const
{
    return Hm;
}

void FullMatrix::read(const string &filename)
{
    Hm.read(filename);
}

void FullMatrix::write(const string &filename) const
{
    Hm.write(filename);
}

size_t FullMatrix::getWfSize() const
{
    return Hm.rank(0);
}

void FullMatrix::applyHToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew) const
{
    if( wfNew.size() != wf.size() ) wfNew.resize( wf.size() );
    gemv_cpu( Hm, wf.getWf(), wfNew.wfRef() );
}

FullMatrix::FullMatrix(const FullMatrix& x) {}

FullMatrix & FullMatrix::operator  = (const FullMatrix& x) { return *this; }