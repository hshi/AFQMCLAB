//
// Created by boruoshihao on 12/28/16.
//

#include "../include/hop.h"

using namespace std;
using namespace tensor_hao;

Hop::Hop():logw(0.0) { }

Hop::Hop(size_t L):logw(0.0) { matrix.resize(L, L); }

Hop::Hop(const Hop &x) { copy_deep(x); }

Hop::Hop(Hop &&x) { move_deep(x); }

Hop::~Hop() { }

Hop &Hop::operator=(const Hop &x)  { copy_deep(x); return *this; }

Hop &Hop::operator=(Hop &&x) { move_deep(x); return *this; }

size_t Hop::getL() const { return matrix.rank(0); }

double Hop::getMemory() const
{
    return 16.0+matrix.getMemory();
}

void Hop::copy_deep(const Hop &x)
{
    logw = x.logw;
    matrix = x.matrix;
}

void Hop::move_deep(Hop &x)
{
    logw = x.logw;
    matrix = move( x.matrix );
}
