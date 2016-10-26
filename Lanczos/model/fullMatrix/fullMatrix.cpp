//
// Created by boruoshihao on 10/25/16.
//

#include <fstream>
#include "fullMatrix.h"

using namespace std;
using namespace tensor_hao;

FullMatrix::FullMatrix()  { }

FullMatrix::FullMatrix(const TensorHao<complex<double>, 2> &HmIn)
{
    Hm.resize( HmIn.getRank() );
    copy_cpu(HmIn, Hm);
}

FullMatrix::FullMatrix(TensorHao<complex<double>, 2> &&HmIn)
{
    Hm = move( HmIn );
}

const TensorHao<complex<double>, 2> &FullMatrix::getHm() const
{
    return Hm;
}

void FullMatrix::read(const string &filename)
{
    size_t fileSize; double real,imag;

    ifstream file;
    file.open(filename, ios::in);
    if( !file.is_open() ) { cout << "Error opening file for FullMatrix::read!!!"; exit(1); }
    file>>fileSize;
    size_t L = sqrt(fileSize);
    if( L*L != fileSize ) { cout<<"Error!!! File size does not fit into a sqare matrix."<<endl; exit(1); }
    if( Hm.size() != fileSize )  Hm.resize( L, L );

    complex<double> * Hmpointer = Hm.data();
    for(size_t i = 0; i < fileSize; ++i)
    {
        file >> real >> imag;
        Hmpointer[i] = complex<double>(real, imag);
    }
    file.close();
}

void FullMatrix::write(const string &filename) const
{
    const complex<double> * Hmpointer = Hm.data();

    ofstream file;
    file.open(filename, ios::out|ios::trunc);
    if( !file.is_open() ) { cout << "Error opening file for FullMatrix::write!!!"; exit(1); }
    file<<setprecision(16)<<scientific;
    file << Hm.size();
    for(size_t i = 0; i < Hm.size(); ++i)
    {
        file << setw(26) << Hmpointer[i].real() << setw(26) << Hmpointer[i].imag() <<"\n";
    }
    file.close();
}

size_t FullMatrix::getWfSize() const
{
    return Hm.rank(0);
}

void FullMatrix::applyHToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew) const
{
    if( wfNew.size() != wf.size() ) wfNew.resize( wf.size() );
    gemv_cpu( Hm, wf.getWf(), wfNew.wfRef() );
}

FullMatrix::FullMatrix(const FullMatrix& x) {}

FullMatrix & FullMatrix::operator  = (const FullMatrix& x) { return *this; }