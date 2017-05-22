//
// Created by boruoshihao on 5/18/17.
//

#include "../include/logHop2is.h"

using namespace std;
using namespace tensor_hao;

LogHop2is::LogHop2is():logw(0) { }

LogHop2is::LogHop2is(size_t L):logw(0) { matrix.resize(L, L); }

LogHop2is::LogHop2is(const LogHop2is &x) { copy_deep(x); }

LogHop2is::LogHop2is(LogHop2is &&x) { move_deep(x); }

LogHop2is::~LogHop2is() { }

LogHop2is &LogHop2is::operator=(const LogHop2is &x)  { copy_deep(x); return *this; }

LogHop2is &LogHop2is::operator=(LogHop2is &&x) { move_deep(x); return *this; }

size_t LogHop2is::getL() const { return matrix.rank(0); }

double LogHop2is::getMemory() const
{
    return 16.0+matrix.getMemory();
}

void LogHop2is::copy_deep(const LogHop2is &x)
{
    logw = x.logw;
    matrix = x.matrix;
}

void LogHop2is::move_deep(LogHop2is &x)
{
    logw = x.logw;
    matrix = move( x.matrix );
}