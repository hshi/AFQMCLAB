//
// Created by boruoshihao on 11/18/16.
//
#include "../include/SpinlessFermions.h"
#include "../../../../libhao/mathHao/include/simple_fun.h"

using namespace std;

SpinlessFermions::SpinlessFermions(size_t L, size_t N) : L(L), N(N)
{
    Nhilbert = binomialCoeff(L, N);
}

SpinlessFermions::SpinlessFermions(const string &filename)
{
    read(filename);
}

size_t SpinlessFermions::getL() const { return L; }

size_t SpinlessFermions::getN() const { return N; }

const vector<LanOneBody> &SpinlessFermions::getK() const { return K; }

const vector<LanTwoBody> &SpinlessFermions::getV() const { return V; }

size_t SpinlessFermions::getWfSize() const { return Nhilbert; }

void SpinlessFermions::setK(const vector<LanOneBody> &K) { SpinlessFermions::K = K; }

void SpinlessFermions::setV(const vector<LanTwoBody> &V) { SpinlessFermions::V = V; }

SpinlessFermions::SpinlessFermions(const SpinlessFermions &x) { }

SpinlessFermions &SpinlessFermions::operator=(const SpinlessFermions &x) { return *this; }
