//
// Created by boruoshihao on 1/9/17.
//

#include "../include/NiupNidnSample.h"

using namespace std;
using namespace tensor_hao;

NiupNidnSample::NiupNidnSample():logw(0.0) { }

NiupNidnSample::NiupNidnSample(size_t L):logw(0.0)
{
    diag00.resize(L);
    diag10.resize(L);
    diag01.resize(L);
    diag11.resize(L);
}

NiupNidnSample::NiupNidnSample(const NiupNidnSample &x) { copy_deep(x);}

NiupNidnSample::NiupNidnSample(NiupNidnSample &&x) { move_deep(x); }

NiupNidnSample::~NiupNidnSample() { }

NiupNidnSample &NiupNidnSample::operator=(const NiupNidnSample &x) { copy_deep(x); return *this; }

NiupNidnSample &NiupNidnSample::operator=(NiupNidnSample &&x) { move_deep(x); return *this; }

size_t NiupNidnSample::getL() const { return diag00.size(); }

double NiupNidnSample::getMemory() const
{
    return 16.0+diag00.getMemory()+diag01.getMemory()+diag10.getMemory()+diag11.getMemory();
}

void NiupNidnSample::copy_deep(const NiupNidnSample &x)
{
    logw = x.logw;
    diag00 = x.diag00;
    diag10 = x.diag10;
    diag01 = x.diag01;
    diag11 = x.diag11;
}

void NiupNidnSample::move_deep(NiupNidnSample &x)
{
    logw = x.logw;
    diag00 = move( x.diag00 );
    diag10 = move( x.diag10 );
    diag01 = move( x.diag01 );
    diag11 = move( x.diag11 );
}
