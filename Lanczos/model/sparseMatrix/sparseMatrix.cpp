//
// Created by boruoshihao on 10/26/16.
//
#include <fstream>
#include "sparseMatrix.h"

using namespace std;

using namespace tensor_hao;

SparseMatrix::SparseMatrix(): matrixRank(0) { }

SparseMatrix::SparseMatrix(size_t  L, const std::vector<SparseElement> &HmIn)
{
    matrixRank = L;
    Hm = HmIn;
}

SparseMatrix::SparseMatrix(size_t  L, std::vector<SparseElement> &&HmIn)
{
    matrixRank = L;
    Hm = move( HmIn );
}

const std::vector<SparseElement> &SparseMatrix::getHm() const
{
    return Hm;
}

void SparseMatrix::read(const std::string &filename)
{
    size_t fileSize;

    ifstream file;
    file.open(filename, ios::in);
    if( !file.is_open() ) { cout << "Error opening file for SparseMatrix::read!!!"; exit(1); }
    file>>matrixRank;
    file>>fileSize;
    if( Hm.size() != fileSize )  Hm.resize( fileSize );

    size_t indexI, indexJ; double real, imag;

    for(size_t i = 0; i < fileSize; ++i)
    {
        file >> indexI >>indexJ >> real >> imag;
        Hm[i] = { indexI, indexJ, complex<double>(real, imag) };
    }

    file.close();
}

void SparseMatrix::write(const std::string &filename) const
{
    ofstream file;
    file.open(filename, ios::out|ios::trunc);
    if( !file.is_open() ) { cout << "Error opening file for SparseMatrix::write!!!"; exit(1); }
    file<<setprecision(16)<<scientific;
    file<<matrixRank<<"\n";
    file<<Hm.size()<<"\n";
    for(size_t k = 0; k < Hm.size(); ++k)
    {
        file << setw(26) << Hm[k].i
             << setw(26) << Hm[k].j
             << setw(26) << Hm[k].h.real()
             << setw(26) << Hm[k].h.imag()
             <<"\n";
    }
    file.close();
}

size_t SparseMatrix::getWfSize() const
{
    return matrixRank;
}

void SparseMatrix::applyHToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew) const
{
    if( wfNew.size() != wf.size() ) wfNew.resize( wf.size() );

    const TensorHao<complex<double>, 1> & vec = wf.getWf();
    TensorHao<complex<double>, 1> & vecNew = wfNew.wfRef();
    size_t HmSize = Hm.size();

    vecNew = complex<double>(0,0);
    //TODO: ADD OPENMP HERE? How to avoid two thread working together?
    for(size_t k = 0; k < HmSize; ++k)
    {
        vecNew( Hm[k].i ) += Hm[k].h * vec( Hm[k].j );
    }
}

SparseMatrix::SparseMatrix(const SparseMatrix &x)  { }

SparseMatrix &SparseMatrix::operator=(const SparseMatrix &x) { return *this; }
