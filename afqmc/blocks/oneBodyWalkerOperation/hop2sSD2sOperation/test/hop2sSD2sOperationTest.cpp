//
// Created by boruoshihao on 5/17/17.
//

#include "../include/hop2sSD2sOperation.h"
#include "../../../../../common/testHao/gtest_custom.h"

using namespace std;
using namespace tensor_hao;

class Hop2sSD2sOperationTest: public ::testing::Test
{
 public:
    size_t L, Nup, Ndn;
    TensorHao<complex<double>,2> matrixUp, matrixDn, wfUpOld, wfDnOld, wfRightUpNew, wfRightDnNew, wfLeftUpNew, wfLeftDnNew;

    Hop2sSD2sOperationTest( )
    {
        L=10; Nup=5; Ndn=3;

        matrixUp.resize(L,L); matrixDn.resize(L,L);
        wfUpOld.resize(L,Nup); wfDnOld.resize(L,Ndn);
        wfRightUpNew.resize(L,Nup); wfRightDnNew.resize(L,Ndn);
        wfLeftUpNew.resize(L,Nup); wfLeftDnNew.resize(L,Ndn);

        gmm_cpu(matrixUp, wfUpOld, wfRightUpNew);
        gmm_cpu(matrixDn, wfDnOld, wfRightDnNew);
        gmm_cpu(matrixUp, wfUpOld, wfLeftUpNew, 'C');
        gmm_cpu(matrixDn, wfDnOld, wfLeftDnNew, 'C');
    }

    ~Hop2sSD2sOperationTest( )  {}
};

TEST_F(Hop2sSD2sOperationTest, applyToRight)
{
    SD2s sd2s(L,Nup, Ndn), sd2sNew;
    Hop2s hop2s; hop2s.logw=complex<double>(1.2,1.5); hop2s.matrixUp=matrixUp; hop2s.matrixDn = matrixDn;
    sd2s.logwRef()=1.6; sd2s.wfUpRef() = wfUpOld; sd2s.wfDnRef() = wfDnOld;

    Hop2sSD2sOperation hop2sSD2sOperation;
    hop2sSD2sOperation.applyToRight(hop2s, sd2s, sd2sNew);

    EXPECT_FALSE( diff(wfRightUpNew, sd2sNew.getWfUp(), 1e-12) );
    EXPECT_FALSE( diff(wfRightDnNew, sd2sNew.getWfDn(), 1e-12) );
    EXPECT_COMPLEXDOUBLE_EQ( complex<double>(2.8, 1.5), sd2sNew.getLogw() );
}

TEST_F(Hop2sSD2sOperationTest, applyToLeft)
{
    SD2s sd2s(L,Nup, Ndn), sd2sNew;
    Hop2s hop2s; hop2s.logw=complex<double>(1.2,1.5); hop2s.matrixUp=matrixUp; hop2s.matrixDn = matrixDn;
    sd2s.logwRef()=1.6; sd2s.wfUpRef() = wfUpOld; sd2s.wfDnRef() = wfDnOld;

    Hop2sSD2sOperation hop2sSD2sOperation;
    hop2sSD2sOperation.applyToLeft(hop2s, sd2s, sd2sNew);

    EXPECT_FALSE( diff(wfLeftUpNew, sd2sNew.getWfUp(), 1e-12) );
    EXPECT_FALSE( diff(wfLeftDnNew, sd2sNew.getWfDn(), 1e-12) );
    EXPECT_COMPLEXDOUBLE_EQ( complex<double>(2.8, -1.5), sd2sNew.getLogw() );
}