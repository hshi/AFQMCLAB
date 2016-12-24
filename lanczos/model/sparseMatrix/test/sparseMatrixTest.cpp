//
// Created by boruoshihao on 10/26/16.
//

#include "../../../../common/testHao/gtest_custom.h"
#include "../../../interface/include/LanczosInterface.h"
#include "../include/sparseMatrix.h"

using namespace std;
using namespace tensor_hao;

class lanczosModelSparseMatrixTest: public ::testing::Test
{
 public:
    size_t L = 30;
    size_t nonZeroSize;

    TensorHao<complex<double>, 2 > Hv;
    TensorHao<double,1> Hd;

    TensorHao<complex<double>, 1> values;
    TensorHao<size_t, 1> columnIndex,rowPointer;

    lanczosModelSparseMatrixTest( )
    {
        createHvGetNonZeroSize();

        fillValuesColumnRow();

        getHdAndHv();
    }

    void createHvGetNonZeroSize()
    {
        Hv.resize(L,L);
        randomFill(Hv);
        Hv += conjtrans(Hv);

        nonZeroSize = 0;
        for(size_t i = 0; i < L; ++i)
        {
            for(size_t j = 0; j < L; ++j)
            {
                if( abs( Hv(i,j) ) > 0.5  ) nonZeroSize++;
                else Hv(i,j)=0.0;
            }
        }
    }

    void fillValuesColumnRow()
    {
        values.resize(nonZeroSize); columnIndex.resize(nonZeroSize); rowPointer.resize(L+1);

        size_t valuesIndex=0;
        rowPointer(0) = 0;
        for(size_t i = 0; i < L; ++i)
        {
            for(size_t j = 0; j < L; ++j)
            {
                if(abs( Hv(i, j) ) > 1e-12  )
                {
                    values(valuesIndex ) = Hv(i, j);
                    columnIndex(valuesIndex) = j;
                    valuesIndex++;
                }
            }
            rowPointer(i + 1) = valuesIndex;
        }
    }

    void getHdAndHv()
    {
        Hd.resize(L);
        eigen_cpu(Hv, Hd);
    }

    ~lanczosModelSparseMatrixTest( )
    {
    }
};

TEST_F(lanczosModelSparseMatrixTest, copyConstructor)
{
    SparseMatrix sm(values, columnIndex, rowPointer);

    EXPECT_EQ( L, sm.getWfSize() );
    EXPECT_FALSE( diff(values, sm.getValues(), 1e-12) );
    EXPECT_FALSE( diff(columnIndex, sm.getColumnIndex(), 1e-12) );
    EXPECT_FALSE( diff(rowPointer, sm.getRowPointer(), 1e-12) );
}

TEST_F(lanczosModelSparseMatrixTest, moveConstructor)
{
    TensorHao<complex<double>, 1> v(values);
    TensorHao<size_t, 1> c(columnIndex),r(rowPointer);
    SparseMatrix sm( move(v), move(c), move(r) );

    EXPECT_FALSE( v.data() );
    EXPECT_FALSE( c.data() );
    EXPECT_FALSE( r.data() );

    EXPECT_EQ( L, sm.getWfSize() );
    EXPECT_FALSE( diff(values, sm.getValues(), 1e-12) );
    EXPECT_FALSE( diff(columnIndex, sm.getColumnIndex(), 1e-12) );
    EXPECT_FALSE( diff(rowPointer, sm.getRowPointer(), 1e-12) );
}

TEST_F(lanczosModelSparseMatrixTest, readWrite)
{
    string filename = "sparseMatrix.dat";
    SparseMatrix smp(values, columnIndex, rowPointer);
    smp.write(filename);

    SparseMatrix sm(filename);
    EXPECT_EQ( L, sm.getWfSize() );
    EXPECT_FALSE( diff(values, sm.getValues(), 1e-12) );
    EXPECT_FALSE( diff(columnIndex, sm.getColumnIndex(), 1e-12) );
    EXPECT_FALSE( diff(rowPointer, sm.getRowPointer(), 1e-12) );

    remove( filename.c_str() );
}

TEST_F(lanczosModelSparseMatrixTest, lanczos)
{
    SparseMatrix sm(values, columnIndex, rowPointer);
    Lanczos lan( sm );
    lan.findEigen(1);

    EXPECT_NEAR( Hd(0), lan.getEigenvalue(0), 1e-10 );
}