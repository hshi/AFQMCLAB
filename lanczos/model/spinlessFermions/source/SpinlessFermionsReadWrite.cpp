//
// Created by boruoshihao on 11/19/16.
//
#include <fstream>
#include "../include/SpinlessFermions.h"
#include "../../../../common/mathHao/include/simple_fun.h"

using namespace std;

void SpinlessFermions::read(const string &filename)
{
    size_t vecSize; size_t i, j, k, l; double real,imag;

    ifstream file;
    file.open(filename, ios::in);
    if( !file.is_open() ) { cout << "Error opening file for SpinlessFermions::read!!!"; exit(1); }
    file >> L >> N;

    Nhilbert = binomialCoeff(L, N);

    file >> vecSize;
    if( K.size() != vecSize )  K.resize( vecSize );
    for(size_t m = 0; m < vecSize; ++m)
    {
        file >> i >> j >> real >> imag;
        K[m] = { i, j, complex<double>(real, imag) };
    }

    file >> vecSize;
    if( V.size() != vecSize )  V.resize( vecSize );
    for(size_t m = 0; m < vecSize; ++m)
    {
        file >> i >> j >> k >> l >> real >> imag;
        V[m] = { i, j, k, l, complex<double>(real, imag) };
    }

    file.close();
}

void SpinlessFermions::write(const string &filename)
{
    ofstream file;
    file.open(filename, ios::out|ios::trunc);
    if( !file.is_open() ) { cout << "Error opening file for SpinlessFermions::write!!!"; exit(1); }
    file<<setprecision(16)<<scientific;
    file<<setw(26)<<L<<setw(26)<<N<<"\n";

    file<<setw(26)<<K.size()<<"\n";
    for(size_t m = 0; m < K.size(); ++m)
    {
        file << setw(26) << K[m].i << setw(26) << K[m].j
             << setw(26) << K[m].K.real() << setw(26) << K[m].K.imag() << "\n";
    }

    file<<setw(26)<<V.size()<<"\n";
    for(size_t m = 0; m < V.size(); ++m)
    {
        file << setw(26) << V[m].i << setw(26) << V[m].j
             << setw(26) << V[m].k << setw(26) << V[m].l
             << setw(26) << V[m].V.real() << setw(26) << V[m].V.imag() << "\n";
    }

    file.close();
}