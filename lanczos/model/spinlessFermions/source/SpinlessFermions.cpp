//
// Created by boruoshihao on 11/18/16.
//
#include "../include/SpinlessFermions.h"
#include "../../../../common/mathHao/include/simple_fun.h"

using namespace std;

SpinlessFermions::SpinlessFermions(size_t L, size_t N) : L(L), N(N)
{
    Nhilbert = binomialCoeff(L, N);
    printMemoryInfo();
}

SpinlessFermions::SpinlessFermions(const string &filename)
{
    read(filename);
    printMemoryInfo();
}

SpinlessFermions::SpinlessFermions(const SpinlessFermions &x) { copy_deep(x); }

SpinlessFermions::SpinlessFermions(SpinlessFermions &&x) { move_deep(x); }

SpinlessFermions &SpinlessFermions::operator=(const SpinlessFermions &x) { copy_deep(x); return *this; }

SpinlessFermions &SpinlessFermions::operator=(SpinlessFermions &&x) { move_deep(x); return *this; }

SpinlessFermions SpinlessFermions::generateNewModel(size_t L, size_t N)
{
    SpinlessFermions H(L, N);
    H.setK(K); H.setV(V);
    return H;
}


size_t SpinlessFermions::getL() const { return L; }

size_t SpinlessFermions::getN() const { return N; }

const vector<LanOneBody> &SpinlessFermions::getK() const { return K; }

const vector<LanTwoBody> &SpinlessFermions::getV() const { return V; }

size_t SpinlessFermions::getWfSize() const { return Nhilbert; }

void SpinlessFermions::setK(const vector<LanOneBody> &K) { SpinlessFermions::K = K; }

void SpinlessFermions::setV(const vector<LanTwoBody> &V) { SpinlessFermions::V = V; }

void SpinlessFermions::printMemoryInfo()
{
    double mem;
    cout<<endl;

    mem = sizeof(complex<double>) * Nhilbert;
    cout<<"Memory for one Lanczos basis wave function is "<<mem/1e9<<"GB"<<endl;

    cout<<endl;
}

void SpinlessFermions::copy_deep(const SpinlessFermions &x)
{
    L = x.L;
    N = x.N;
    K = x.K;
    V = x.V;
    Nhilbert = x.Nhilbert;
}

void SpinlessFermions::move_deep(SpinlessFermions &x)
{
    L = x.L;
    N = x.N;
    K = move( x.K );
    V = move( x.V );
    Nhilbert = x.Nhilbert;
}
