//
// Created by boruoshihao on 5/17/17.
//

#include "../include/hop2s.h"

using namespace std;
using namespace tensor_hao;

Hop2s::Hop2s():logw(0.0) { }

Hop2s::Hop2s(size_t L):logw(0.0)
{
    matrixUp.resize(L,L);
    matrixDn.resize(L,L);
}

Hop2s::Hop2s(const Hop2s &x) { copy_deep(x); }

Hop2s::Hop2s(Hop2s &&x) { move_deep(x); }

Hop2s::~Hop2s() { }

Hop2s &Hop2s::operator=(const Hop2s &x)  { copy_deep(x); return *this; }

Hop2s &Hop2s::operator=(Hop2s &&x) { move_deep(x); return *this; }

size_t Hop2s::getL() const { return matrixUp.rank(0); }

double Hop2s::getMemory() const
{
    return 16.0+matrixUp.getMemory()+matrixDn.getMemory();
}

void Hop2s::copy_deep(const Hop2s &x)
{
    logw = x.logw;
    matrixUp = x.matrixUp;
    matrixDn = x.matrixDn;
}

void Hop2s::move_deep(Hop2s &x)
{
    logw = x.logw;
    matrixUp = move( x.matrixUp );
    matrixDn = move( x.matrixDn );
}
