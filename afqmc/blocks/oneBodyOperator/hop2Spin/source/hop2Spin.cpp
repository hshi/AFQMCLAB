//
// Created by boruoshihao on 5/17/17.
//

#include "../include/hop2Spin.h"

using namespace std;
using namespace tensor_hao;

Hop2Spin::Hop2Spin():logw(0.0) { }

Hop2Spin::Hop2Spin(size_t L):logw(0.0)
{
    matrixUp.resize(L,L);
    matrixDn.resize(L,L);
}

Hop2Spin::Hop2Spin(const Hop2Spin &x) { copy_deep(x); }

Hop2Spin::Hop2Spin(Hop2Spin &&x) { move_deep(x); }

Hop2Spin::~Hop2Spin() { }

Hop2Spin &Hop2Spin::operator=(const Hop2Spin &x)  { copy_deep(x); return *this; }

Hop2Spin &Hop2Spin::operator=(Hop2Spin &&x) { move_deep(x); return *this; }

size_t Hop2Spin::getL() const { return matrixUp.rank(0); }

double Hop2Spin::getMemory() const
{
    return 16.0+matrixUp.getMemory()+matrixDn.getMemory();
}

void Hop2Spin::copy_deep(const Hop2Spin &x)
{
    logw = x.logw;
    matrixUp = x.matrixUp;
    matrixDn = x.matrixDn;
}

void Hop2Spin::move_deep(Hop2Spin &x)
{
    logw = x.logw;
    matrixUp = move( x.matrixUp );
    matrixDn = move( x.matrixDn );
}
