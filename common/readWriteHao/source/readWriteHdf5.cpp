//
// Created by boruoshihao on 5/31/17.
//

#include "../include/readWriteHdf5.h"

using namespace std;
using namespace H5;

void readFile(size_t &data, const H5File &file, const string &dataSetName)
{
    DataSet dataset = file.openDataSet( dataSetName );
    size_t dataSize = returnDataSetSize(dataset);
    if( dataSize != 1 ) { cout<<"Error, dataset size is not consistent with pointer size."<<endl; exit(1); }
    dataset.read( &data, PredType::NATIVE_ULONG );
}

void readFile(double &data, const H5File &file, const string &dataSetName)
{
    DataSet dataset = file.openDataSet( dataSetName );
    size_t dataSize = returnDataSetSize(dataset);
    if( dataSize != 1 ) { cout<<"Error, dataset size is not consistent with pointer size."<<endl; exit(1); }
    dataset.read( &data, PredType::NATIVE_DOUBLE );
}

void readFile(complex<double> &data, const H5File &file, const string &dataSetName)
{
    DataSet dataset = file.openDataSet( dataSetName );
    size_t dataSize = returnDataSetSize(dataset);
    if( dataSize != 1 ) { cout<<"Error, dataset size is not consistent with pointer size."<<endl; exit(1); }
    dataset.read( &data, returnComplexDoubleCompType(PredType::NATIVE_DOUBLE) );
}

void readFile(size_t L, size_t *data, const H5File &file, const string &dataSetName)
{
    DataSet dataset = file.openDataSet( dataSetName );
    size_t dataSize = returnDataSetSize(dataset);
    if( dataSize != L ) { cout<<"Error, dataset size is not consistent with pointer size."<<endl; exit(1); }
    dataset.read( data, PredType::NATIVE_ULONG );
}

void readFile(size_t L, double *data, const H5File &file, const string &dataSetName)
{
    DataSet dataset = file.openDataSet( dataSetName );
    size_t dataSize = returnDataSetSize(dataset);
    if( dataSize != L ) { cout<<"Error, dataset size is not consistent with pointer size."<<endl; exit(1); }
    dataset.read( data, PredType::NATIVE_DOUBLE );
}

void readFile(size_t L, complex<double> *data, const H5File &file, const string &dataSetName)
{
    DataSet dataset = file.openDataSet( dataSetName );
    size_t dataSize = returnDataSetSize(dataset);
    if( dataSize != L ) { cout<<"Error, dataset size is not consistent with pointer size."<<endl; exit(1); }
    dataset.read( data, returnComplexDoubleCompType(PredType::NATIVE_DOUBLE) );
}

void writeFile(const size_t &data, H5File &file, const string &dataSetName)
{
    if( H5Lexists(file.getId(), dataSetName.data(), H5P_DEFAULT) ) H5Ldelete(file.getId(), dataSetName.data(), H5P_DEFAULT);
    DataSet dataset = file.createDataSet( dataSetName, PredType::STD_U64BE, returnDataspace(1) );
    dataset.write(&data, PredType::NATIVE_ULONG);
}

void writeFile(const double &data, H5File &file, const string &dataSetName)
{
    if( H5Lexists(file.getId(), dataSetName.data(), H5P_DEFAULT) ) H5Ldelete(file.getId(), dataSetName.data(), H5P_DEFAULT);
    DataSet dataset = file.createDataSet( dataSetName, PredType::IEEE_F64BE, returnDataspace(1) );
    dataset.write(&data, PredType::NATIVE_DOUBLE);
}

void writeFile(const complex<double> &data, H5File &file, const string &dataSetName)
{
    if( H5Lexists(file.getId(), dataSetName.data(), H5P_DEFAULT) ) H5Ldelete(file.getId(), dataSetName.data(), H5P_DEFAULT);
    DataSet dataset = file.createDataSet( dataSetName, returnComplexDoubleCompType(PredType::IEEE_F64BE), returnDataspace(1) );
    dataset.write(&data, returnComplexDoubleCompType(PredType::NATIVE_DOUBLE));
}

void writeFile(size_t L, const size_t *data, H5::H5File &file, const std::string &dataSetName)
{
    if( H5Lexists(file.getId(), dataSetName.data(), H5P_DEFAULT) ) H5Ldelete(file.getId(), dataSetName.data(), H5P_DEFAULT);
    DataSet dataset = file.createDataSet( dataSetName, PredType::STD_U64BE,  returnDataspace(L) );
    dataset.write(data, PredType::NATIVE_ULONG);
}

void writeFile(size_t L, const double *data, H5File &file, const string &dataSetName)
{
    if( H5Lexists(file.getId(), dataSetName.data(), H5P_DEFAULT) ) H5Ldelete(file.getId(), dataSetName.data(), H5P_DEFAULT);
    DataSet dataset = file.createDataSet( dataSetName, PredType::IEEE_F64BE,  returnDataspace(L) );
    dataset.write(data, PredType::NATIVE_DOUBLE);
}

void writeFile(size_t L, const complex<double> *data, H5File &file, const string &dataSetName)
{
    if( H5Lexists(file.getId(), dataSetName.data(), H5P_DEFAULT) ) H5Ldelete(file.getId(), dataSetName.data(), H5P_DEFAULT);
    DataSet dataset = file.createDataSet( dataSetName, returnComplexDoubleCompType(PredType::IEEE_F64BE), returnDataspace(L) );
    dataset.write(data, returnComplexDoubleCompType(PredType::NATIVE_DOUBLE));
}