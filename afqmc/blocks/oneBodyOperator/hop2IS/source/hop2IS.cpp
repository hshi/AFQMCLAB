//
// Created by boruoshihao on 5/18/17.
//

#include "../include/hop2IS.h"

using namespace std;
using namespace tensor_hao;

Hop2IS::Hop2IS():logw(0.0) { }

Hop2IS::Hop2IS(size_t L):logw(0.0) { matrix.resize(L, L); }

Hop2IS::Hop2IS(const Hop2IS &x) { copy_deep(x); }

Hop2IS::Hop2IS(Hop2IS &&x) { move_deep(x); }

Hop2IS::~Hop2IS() { }

Hop2IS &Hop2IS::operator=(const Hop2IS &x)  { copy_deep(x); return *this; }

Hop2IS &Hop2IS::operator=(Hop2IS &&x) { move_deep(x); return *this; }

size_t Hop2IS::getL() const { return matrix.rank(0); }

double Hop2IS::getMemory() const
{
    return 16.0+matrix.getMemory();
}

void Hop2IS::copy_deep(const Hop2IS &x)
{
    logw = x.logw;
    matrix = x.matrix;
}

void Hop2IS::move_deep(Hop2IS &x)
{
    logw = x.logw;
    matrix = move( x.matrix );
}
