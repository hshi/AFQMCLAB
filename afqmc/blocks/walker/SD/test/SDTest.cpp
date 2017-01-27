//
// Created by boruoshihao on 12/25/16.
//

#include "../include/SD.h"
#include "../../../../../common/testHao/gtest_custom.h"
#include "../../../../../common/readWriteHao/include/readWriteHao.h"

using namespace std;
using namespace tensor_hao;

TEST(SDTest, voidConstruction)
{
    SD sd;
    EXPECT_COMPLEXDOUBLE_EQ( 0.0, sd.getLogw() );
    EXPECT_FALSE( sd.getWf().data() );
    EXPECT_EQ( static_cast<size_t>(0), sd.getL() );
    EXPECT_EQ( static_cast<size_t>(0), sd.getN() );
}

TEST(SDTest, LNConstruction)
{
    size_t L(10), N(5);
    SD sd(L, N);
    EXPECT_COMPLEXDOUBLE_EQ( 0.0, sd.getLogw() );
    EXPECT_TRUE( sd.getWf().data() );
    EXPECT_EQ( L, sd.getL() );
    EXPECT_EQ( N, sd.getN() );
}

TEST(SDTest, copyConstruction)
{
    size_t L(10), N(5);
    TensorHao<complex<double>,2> wf(L,N);
    randomFill(wf);
    complex<double> logw(2.0, 3.0);

    SD sdBase(L, N);
    sdBase.wfRef() = wf;
    sdBase.logwRef() = logw;

    SD sd(sdBase);
    EXPECT_COMPLEXDOUBLE_EQ( logw, sd.getLogw() );
    EXPECT_FALSE( diff( wf, sd.getWf(), 1e-12 ) );
    EXPECT_EQ( L, sd.getL() );
    EXPECT_EQ( N, sd.getN() );
    EXPECT_FALSE( diff( wf, sdBase.getWf(), 1e-12 ) );
}

TEST(SDTest, moveConstruction)
{
    size_t L(10), N(5);
    TensorHao<complex<double>,2> wf(L,N);
    randomFill(wf);
    complex<double> logw(2.0, 3.0);

    SD sdBase(L, N);
    sdBase.wfRef() = wf;
    sdBase.logwRef() = logw;

    SD sd( move(sdBase) );
    EXPECT_COMPLEXDOUBLE_EQ( logw, sd.getLogw() );
    EXPECT_FALSE( diff( wf, sd.getWf(), 1e-12 ) );
    EXPECT_EQ( L, sd.getL() );
    EXPECT_EQ( N, sd.getN() );
    EXPECT_FALSE( sdBase.getWf().data() );
}

TEST(SDTest, copyAssignment)
{
    size_t L(10), N(5);
    TensorHao<complex<double>,2> wf(L,N);
    randomFill(wf);
    complex<double> logw(2.0, 3.0);

    SD sdBase(L, N);
    sdBase.wfRef() = wf;
    sdBase.logwRef() = logw;

    SD sd;  sd = sdBase;
    EXPECT_COMPLEXDOUBLE_EQ( logw, sd.getLogw() );
    EXPECT_FALSE( diff( wf, sd.getWf(), 1e-12 ) );
    EXPECT_EQ( L, sd.getL() );
    EXPECT_EQ( N, sd.getN() );
    EXPECT_FALSE( diff( wf, sdBase.getWf(), 1e-12 ) );
}

TEST(SDTest, moveAssignment)
{
    size_t L(10), N(5);
    TensorHao<complex<double>,2> wf(L,N);
    randomFill(wf);
    complex<double> logw(2.0, 3.0);

    SD sdBase(L, N);
    sdBase.wfRef() = wf;
    sdBase.logwRef() = logw;

    SD sd; sd = move(sdBase);
    EXPECT_COMPLEXDOUBLE_EQ( logw, sd.getLogw() );
    EXPECT_FALSE( diff( wf, sd.getWf(), 1e-12 ) );
    EXPECT_EQ( L, sd.getL() );
    EXPECT_EQ( N, sd.getN() );
    EXPECT_FALSE( sdBase.getWf().data() );
}

TEST(SDTest, readWriteBcast)
{
    size_t L(10), N(5);
    TensorHao<complex<double>,2> wf(L,N);
    randomFill(wf);
    complex<double> logw(2.0, 3.0);

    SD sdBase, sd;
    sdBase.wfRef() = wf;
    sdBase.logwRef() = logw;

    string filename="latt_param.dat";
    if( MPIRank() == 0 ) sdBase.write(filename);
    if( MPIRank() == 0 ) sd.read(filename);
    MPIBcast(sd);
    removeFile(filename);

    EXPECT_COMPLEXDOUBLE_EQ( logw, sd.getLogw() );
    EXPECT_FALSE( diff( wf, sd.getWf(), 1e-12 ) );
    EXPECT_EQ( L, sd.getL() );
    EXPECT_EQ( N, sd.getN() );
}