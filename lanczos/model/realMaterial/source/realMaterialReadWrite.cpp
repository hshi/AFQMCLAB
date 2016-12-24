//
// Created by boruoshihao on 10/27/16.
//

#include <fstream>
#include "../include/realMaterial.h"

using namespace std;
using namespace tensor_hao;

void RealMaterial::read(const std::string &filename)
{
    size_t vecSize; size_t i, j, k, l; double real,imag;

    ifstream file;
    file.open(filename, ios::in);
    if( !file.is_open() ) { cout << "Error opening file for RealMaterial::read!!!"; exit(1); }
    file >> L >> Nup >> Ndn;

    setFromLNupNdn();

    file >> vecSize;
    if( up.size() != vecSize )  up.resize( vecSize );
    for(size_t m = 0; m < vecSize; ++m)
    {
        file >> i >> j >> real >> imag;
        up[m] = { i, j, complex<double>(real, imag) };
    }

    file >> vecSize;
    if( dn.size() != vecSize )  dn.resize( vecSize );
    for(size_t m = 0; m < vecSize; ++m)
    {
        file >> i >> j >> real >> imag;
        dn[m] = { i, j, complex<double>(real, imag) };
    }

    file >> vecSize;
    if( upUp.size() != vecSize )  upUp.resize( vecSize );
    for(size_t m = 0; m < vecSize; ++m)
    {
        file >> i >> j >> k >> l >> real >> imag;
        upUp[m] = { i, j, k, l, complex<double>(real, imag) };
    }

    file >> vecSize;
    if( upDn.size() != vecSize )  upDn.resize( vecSize );
    for(size_t m = 0; m < vecSize; ++m)
    {
        file >> i >> j >> k >> l >> real >> imag;
        upDn[m] = { i, j, k, l, complex<double>(real, imag) };
    }

    file >> vecSize;
    if( dnDn.size() != vecSize )  dnDn.resize( vecSize );
    for(size_t m = 0; m < vecSize; ++m)
    {
        file >> i >> j >> k >> l >> real >> imag;
        dnDn[m] = { i, j, k, l, complex<double>(real, imag) };
    }

    file.close();
}

void RealMaterial::write(const std::string &filename)
{
    ofstream file;
    file.open(filename, ios::out|ios::trunc);
    if( !file.is_open() ) { cout << "Error opening file for RealMaterial::write!!!"; exit(1); }
    file<<setprecision(16)<<scientific;
    file<<setw(26)<<L<<setw(26)<<Nup<<setw(26)<<Ndn<<"\n";

    file<<setw(26)<<up.size()<<"\n";
    for(size_t m = 0; m < up.size(); ++m)
    {
        file << setw(26) << up[m].i << setw(26) << up[m].j
             << setw(26) << up[m].K.real() << setw(26) << up[m].K.imag() << "\n";
    }

    file<<setw(26)<<dn.size()<<"\n";
    for(size_t m = 0; m < dn.size(); ++m)
    {
        file << setw(26) << dn[m].i << setw(26) << dn[m].j
             << setw(26) << dn[m].K.real() << setw(26) << dn[m].K.imag() << "\n";
    }

    file<<setw(26)<<upUp.size()<<"\n";
    for(size_t m = 0; m < upUp.size(); ++m)
    {
        file << setw(26) << upUp[m].i << setw(26) << upUp[m].j
             << setw(26) << upUp[m].k << setw(26) << upUp[m].l
             << setw(26) << upUp[m].V.real() << setw(26) << upUp[m].V.imag() << "\n";
    }

    file<<setw(26)<<upDn.size()<<"\n";
    for(size_t m = 0; m < upDn.size(); ++m)
    {
        file << setw(26) << upDn[m].i << setw(26) << upDn[m].j
             << setw(26) << upDn[m].k << setw(26) << upDn[m].l
             << setw(26) << upDn[m].V.real() << setw(26) << upDn[m].V.imag() << "\n";
    }

    file<<setw(26)<<dnDn.size()<<"\n";
    for(size_t m = 0; m < dnDn.size(); ++m)
    {
        file << setw(26) << dnDn[m].i << setw(26) << dnDn[m].j
             << setw(26) << dnDn[m].k << setw(26) << dnDn[m].l
             << setw(26) << dnDn[m].V.real() << setw(26) << dnDn[m].V.imag() << "\n";
    }
    file.close();
}