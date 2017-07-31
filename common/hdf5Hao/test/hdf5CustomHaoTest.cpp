//
// Created by boruoshihao on 5/30/17.
//

#include "../include/hdf5CustomHao.h"
#include "../../testHao/gtest_custom.h"
#include "../../mpiHao/include/mpi_fun.h"

using namespace std;
using namespace H5;

void removeFile(const string &filename)
{
    string command = "rm -rf " + filename;
    MPIBarrier();
    if( MPIRank()==0 )
    {
        int flag=system( command.c_str() );
        if(flag !=0) cout<<"WARNING!!! system command does not exit properly!"<<endl;
    }
    MPIBarrier();
}

TEST(hdf5Test, returnComplexDoubleCompType)
{
    size_t L=10;
    vector<complex<double>> dataWrite(L), dataRead(L);
    for(size_t i = 0; i < L; ++i) dataWrite[i] = complex<double>(i, i+1);
    string filename("file.h5");

    if( MPIRank()==0 )
    {
        H5File file(filename, H5F_ACC_TRUNC);
        DataSet dataset = file.createDataSet( "data", returnComplexDoubleCompType(PredType::IEEE_F64BE), returnDataspace(L) );
        dataset.write( dataWrite.data(), returnComplexDoubleCompType(PredType::NATIVE_DOUBLE) );
        file.close();
    }
    MPIBarrier();

    H5File file(filename, H5F_ACC_RDONLY);
    DataSet dataset = file.openDataSet("data");
    dataset.read( dataRead.data(), returnComplexDoubleCompType(PredType::NATIVE_DOUBLE) );
    EXPECT_VECOTR_COMPLEXDOUBLE_EQ( dataRead, dataWrite );
    file.close();

    removeFile(filename);
}

TEST(hdf5Test, returnDataSetSize)
{
    size_t L=10;
    string filename("file.h5");

    if( MPIRank()==0 )
    {
        H5File file(filename, H5F_ACC_TRUNC);
        DataSet dataset = file.createDataSet( "data", returnComplexDoubleCompType(PredType::IEEE_F64BE), returnDataspace(L, L-1, L+3) );
        file.close();
    }
    MPIBarrier();

    H5File file(filename, H5F_ACC_RDONLY);
    DataSet dataset = file.openDataSet("data");
    EXPECT_EQ( L*(L-1)*(L+3), returnDataSetSize(dataset) );
    file.close();

    removeFile(filename);
}