//
// Created by boruoshihao on 10/26/16.
//
#include <fstream>
#include "../include/sparseMatrix.h"

using namespace std;
using namespace tensor_hao;

SparseMatrix::SparseMatrix(const TensorHao<complex<double>, 1> &values,
                           const TensorHao<size_t, 1> &columnIndex,
                           const TensorHao<size_t, 1> &rowPointer)
{
    SparseMatrix::values = values;
    SparseMatrix::columnIndex = columnIndex;
    SparseMatrix::rowPointer = rowPointer;
    check();
}

SparseMatrix::SparseMatrix(TensorHao<complex<double>, 1> &&values,
                           TensorHao<size_t, 1> &&columnIndex,
                           TensorHao<size_t, 1> &&rowPointer)
{
    SparseMatrix::values = move( values );
    SparseMatrix::columnIndex = move( columnIndex );
    SparseMatrix::rowPointer = move( rowPointer );
    check();
}

SparseMatrix::SparseMatrix(const string& filename)
{
    read(filename);
    check();
}

const TensorHao<complex<double>, 1> &SparseMatrix::getValues() const { return values; }

const TensorHao<size_t, 1> &SparseMatrix::getColumnIndex() const { return columnIndex; }

const TensorHao<size_t, 1> &SparseMatrix::getRowPointer() const  { return rowPointer; }

void SparseMatrix::read(const std::string &filename)
{
    size_t fileSize;
    double real, imag;

    ifstream file;
    file.open(filename, ios::in);
    if( !file.is_open() ) { cout << "Error opening file for SparseMatrix::read!!!"; exit(1); }

    file>>fileSize;
    if( values.size() != fileSize )  values.resize( fileSize );
    for(size_t i = 0; i < fileSize; ++i)
    {
        file >> real >> imag;
        values(i) = complex<double>(real, imag);
    }

    file>>fileSize;
    if( columnIndex.size() != fileSize )  columnIndex.resize( fileSize );
    for(size_t i = 0; i < fileSize; ++i) file >> columnIndex(i);

    file>>fileSize;
    if( rowPointer.size() != fileSize )  rowPointer.resize( fileSize );
    for(size_t i = 0; i < fileSize; ++i) file >> rowPointer(i);

    file.close();
}

void SparseMatrix::write(const std::string &filename) const
{
    ofstream file;
    file.open(filename, ios::out|ios::trunc);
    if( !file.is_open() ) { cout << "Error opening file for SparseMatrix::write!!!"; exit(1); }
    file<<setprecision(16)<<scientific;

    file<<values.size()<<"\n";
    for(size_t k = 0; k < values.size(); ++k)
    {
        file << setw(26) << values(k).real() << setw(26) << values(k).imag() <<"\n";
    }

    file<<columnIndex.size()<<"\n";
    for(size_t k = 0; k < columnIndex.size(); ++k)
    {
        file << setw(26) << columnIndex(k) <<"\n";
    }

    file<<rowPointer.size()<<"\n";
    for(size_t k = 0; k < rowPointer.size(); ++k)
    {
        file << setw(26) << rowPointer(k) <<"\n";
    }

    file.close();
}

void SparseMatrix::check() const
{
    if( values.size() != columnIndex.size() )
    {
        cout<<"Error!!! values.size() is not consistent with columnIndex.size()!"<<endl;
        exit(1);
    }

    if( rowPointer( rowPointer.size()-1 ) != values.size() )
    {
        cout<<"Error!!! Last element of rowPointer is not consistent with values.size()!"<<endl;
        exit(1);
    }
}

size_t SparseMatrix::getWfSize() const
{
    return rowPointer.size()-1;
}

void SparseMatrix::applyHToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew) const
{
    if( wfNew.size() != wf.size() ) wfNew.resize( wf.size() );

    const TensorHao<complex<double>, 1> & vec = wf.getWf();
    TensorHao<complex<double>, 1> & vecNew = wfNew.wfRef();

    size_t wfSize = wf.size();
    #pragma omp parallel for
    for(size_t i = 0; i < wfSize; ++i)
    {
        vecNew(i) = 0.0;
        for(size_t j = rowPointer(i); j < rowPointer(i+1); ++j)
        {
            vecNew(i) += values(j) * vec( columnIndex(j) );
        }
    }
}

SparseMatrix::SparseMatrix(const SparseMatrix &x)  { }

SparseMatrix &SparseMatrix::operator=(const SparseMatrix &x) { return *this; }