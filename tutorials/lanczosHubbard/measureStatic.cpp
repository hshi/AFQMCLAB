//
// Created by boruoshihao on 4/10/17.
//
#include "afqmclab.h"

using namespace std;
using namespace tensor_hao;

void measureStatic(Lanczos &lan, RealMaterial& H)
{
    size_t L = H.getL();
    const LanczosBasisWf & phi0 = lan.getEigenstate(0);
    LanczosBasisWf & phip = lan.getLanWavefunction(0);

    H.applyKToWf(phi0, phip);
    complex<double> K = phi0.calculateOverlapWith(phip);
    writeFile(K.real(), "K.dat");

    H.applyVToWf(phi0, phip);
    complex<double> V = phi0.calculateOverlapWith(phip);
    writeFile(V.real(), "V.dat");

    TensorHao<complex<double>, 1> SzSz(L);
    for(size_t i = 0; i < L; ++i)
    {
        H.applySziSzjToWf(phi0, phip, 0, i);
        SzSz(i) = phi0.calculateOverlapWith(phip);
    }
    writeFile(SzSz.size(), SzSz.data(), "SzSz.dat");

    TensorHao<complex<double>, 1> SS(L);
    for(size_t i = 0; i < L; ++i)
    {
        H.applySiSjToWf(phi0, phip, 0, i);
        SS(i) = phi0.calculateOverlapWith(phip);
    }
    writeFile(SS.size(), SS.data(), "SS.dat");

    TensorHao<complex<double>, 1> NN(L);
    for(size_t i = 0; i < L; ++i)
    {
        H.applyNiNjToWf(phi0, phip, 0, i);
        NN(i) = phi0.calculateOverlapWith(phip);
    }
    writeFile(NN.size(), NN.data(), "NN.dat");

    TensorHao<complex<double>, 1> DD(L);
    for(size_t i = 0; i < L; ++i)
    {
        H.applyDiDaggerDjToWf(phi0, phip, 0, i);
        DD(i) = phi0.calculateOverlapWith(phip);
    }
    writeFile(DD.size(), DD.data(), "DD.dat");
}