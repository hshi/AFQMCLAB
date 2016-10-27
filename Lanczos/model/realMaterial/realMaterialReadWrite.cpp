//
// Created by boruoshihao on 10/27/16.
//

#include <fstream>
#include "realMaterial.h"

using namespace std;
using namespace tensor_hao;

void RealMaterial::read(const std::string &filename)
{
    size_t vecSize; size_t i, j, k, l; double real,imag;

    ifstream file;
    file.open(filename, ios::in);
    if( !file.is_open() ) { cout << "Error opening file for RealMaterial::read!!!"; exit(1); }
    file >> L >> Nup >> Ndn;

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
    if( upup.size() != vecSize )  upup.resize( vecSize );
    for(size_t m = 0; m < vecSize; ++m)
    {
        file >> i >> j >> k >> l >> real >> imag;
        upup[m] = { i, j, k, l, complex<double>(real, imag) };
    }

    file >> vecSize;
    if( updn.size() != vecSize )  updn.resize( vecSize );
    for(size_t m = 0; m < vecSize; ++m)
    {
        file >> i >> j >> k >> l >> real >> imag;
        updn[m] = { i, j, k, l, complex<double>(real, imag) };
    }

    file >> vecSize;
    if( dnup.size() != vecSize )  dnup.resize( vecSize );
    for(size_t m = 0; m < vecSize; ++m)
    {
        file >> i >> j >> k >> l >> real >> imag;
        dnup[m] = { i, j, k, l, complex<double>(real, imag) };
    }

    file >> vecSize;
    if( dndn.size() != vecSize )  dndn.resize( vecSize );
    for(size_t m = 0; m < vecSize; ++m)
    {
        file >> i >> j >> k >> l >> real >> imag;
        dndn[m] = { i, j, k, l, complex<double>(real, imag) };
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

    file<<setw(26)<<upup.size()<<"\n";
    for(size_t m = 0; m < upup.size(); ++m)
    {
        file << setw(26) << upup[m].i << setw(26) << upup[m].j
             << setw(26) << upup[m].k << setw(26) << upup[m].l
             << setw(26) << upup[m].V.real() << setw(26) << upup[m].V.imag() << "\n";
    }

    file<<setw(26)<<updn.size()<<"\n";
    for(size_t m = 0; m < updn.size(); ++m)
    {
        file << setw(26) << updn[m].i << setw(26) << updn[m].j
             << setw(26) << updn[m].k << setw(26) << updn[m].l
             << setw(26) << updn[m].V.real() << setw(26) << updn[m].V.imag() << "\n";
    }

    file<<setw(26)<<dnup.size()<<"\n";
    for(size_t m = 0; m < dnup.size(); ++m)
    {
        file << setw(26) << dnup[m].i << setw(26) << dnup[m].j
             << setw(26) << dnup[m].k << setw(26) << dnup[m].l
             << setw(26) << dnup[m].V.real() << setw(26) << dnup[m].V.imag() << "\n";
    }

    file<<setw(26)<<dndn.size()<<"\n";
    for(size_t m = 0; m < dndn.size(); ++m)
    {
        file << setw(26) << dndn[m].i << setw(26) << dndn[m].j
             << setw(26) << dndn[m].k << setw(26) << dndn[m].l
             << setw(26) << dndn[m].V.real() << setw(26) << dndn[m].V.imag() << "\n";
    }
    file.close();
}