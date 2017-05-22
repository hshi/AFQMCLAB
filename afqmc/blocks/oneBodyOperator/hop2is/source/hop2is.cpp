//
// Created by boruoshihao on 5/18/17.
//

#include "../include/hop2is.h"

using namespace std;
using namespace tensor_hao;

Hop2is::Hop2is():logw(0.0) { }

Hop2is::Hop2is(size_t L):logw(0.0) { matrix.resize(L, L); }

Hop2is::Hop2is(const Hop2is &x) { copy_deep(x); }

Hop2is::Hop2is(Hop2is &&x) { move_deep(x); }

Hop2is::~Hop2is() { }

Hop2is &Hop2is::operator=(const Hop2is &x)  { copy_deep(x); return *this; }

Hop2is &Hop2is::operator=(Hop2is &&x) { move_deep(x); return *this; }

size_t Hop2is::getL() const { return matrix.rank(0); }

double Hop2is::getMemory() const
{
    return 16.0+matrix.getMemory();
}

void Hop2is::copy_deep(const Hop2is &x)
{
    logw = x.logw;
    matrix = x.matrix;
}

void Hop2is::move_deep(Hop2is &x)
{
    logw = x.logw;
    matrix = move( x.matrix );
}
