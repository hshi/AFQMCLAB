//
// Created by boruoshihao on 5/18/17.
//

#include "../include/logHop2IS.h"

using namespace std;
using namespace tensor_hao;

LogHop2IS::LogHop2IS():logw(0) { }

LogHop2IS::LogHop2IS(size_t L):logw(0) { matrix.resize(L, L); }

LogHop2IS::LogHop2IS(const LogHop2IS &x) { copy_deep(x); }

LogHop2IS::LogHop2IS(LogHop2IS &&x) { move_deep(x); }

LogHop2IS::~LogHop2IS() { }

LogHop2IS &LogHop2IS::operator=(const LogHop2IS &x)  { copy_deep(x); return *this; }

LogHop2IS &LogHop2IS::operator=(LogHop2IS &&x) { move_deep(x); return *this; }

size_t LogHop2IS::getL() const { return matrix.rank(0); }

double LogHop2IS::getMemory() const
{
    return 16.0+matrix.getMemory();
}

void LogHop2IS::copy_deep(const LogHop2IS &x)
{
    logw = x.logw;
    matrix = x.matrix;
}

void LogHop2IS::move_deep(LogHop2IS &x)
{
    logw = x.logw;
    matrix = move( x.matrix );
}