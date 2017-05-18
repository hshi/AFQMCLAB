//
// Created by boruoshihao on 5/17/17.
//

#include "../include/hop2S.h"

using namespace std;
using namespace tensor_hao;

Hop2S::Hop2S():logw(0.0) { }

Hop2S::Hop2S(size_t L):logw(0.0)
{
    matrixUp.resize(L,L);
    matrixDn.resize(L,L);
}

Hop2S::Hop2S(const Hop2S &x) { copy_deep(x); }

Hop2S::Hop2S(Hop2S &&x) { move_deep(x); }

Hop2S::~Hop2S() { }

Hop2S &Hop2S::operator=(const Hop2S &x)  { copy_deep(x); return *this; }

Hop2S &Hop2S::operator=(Hop2S &&x) { move_deep(x); return *this; }

size_t Hop2S::getL() const { return matrixUp.rank(0); }

double Hop2S::getMemory() const
{
    return 16.0+matrixUp.getMemory()+matrixDn.getMemory();
}

void Hop2S::copy_deep(const Hop2S &x)
{
    logw = x.logw;
    matrixUp = x.matrixUp;
    matrixDn = x.matrixDn;
}

void Hop2S::move_deep(Hop2S &x)
{
    logw = x.logw;
    matrixUp = move( x.matrixUp );
    matrixDn = move( x.matrixDn );
}
