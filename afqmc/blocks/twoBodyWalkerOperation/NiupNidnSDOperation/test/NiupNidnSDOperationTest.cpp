//
// Created by boruoshihao on 1/10/17.
//

#include "../include/NiupNidnSDOperation.h"
#include "../../../../../common/testHao/gtest_custom.h"

using namespace std;
using namespace tensor_hao;

class NiupNidnSDOperationTest: public ::testing::Test
{
 public:
    size_t L, N, halfL;
    TensorHao<complex<double>, 2> matrix, wfOld, wfRightNew, wfLeftNew;
    TensorHao<complex<double>, 1> diag00, diag10, diag01, diag11;

    NiupNidnSDOperationTest()
    {
        L=10; N=6; halfL=L/2;
        matrix.resize(L,L);  wfOld.resize(L,N); wfRightNew.resize(L,N); wfLeftNew.resize(L,N);
        diag00.resize(halfL); diag10.resize(halfL); diag01.resize(halfL); diag11.resize(halfL);

        matrix = complex<double>(0,0);
        randomFill(diag00); randomFill(diag01); randomFill(diag10); randomFill(diag11);
        for(size_t i = 0; i < halfL; ++i)
        {
            matrix(i,i)       = diag00(i); matrix(i, i+halfL)       = diag01(i);
            matrix(i+halfL,i) = diag10(i); matrix(i+halfL, i+halfL) = diag11(i);
        }

        randomFill(wfOld);
        gmm_cpu(matrix, wfOld, wfRightNew);
        gmm_cpu(matrix, wfOld, wfLeftNew,'C');
    }

    ~NiupNidnSDOperationTest() {}
};

TEST_F(NiupNidnSDOperationTest, applyToRight)
{
    SD sd(L,N), sdNew;
    sd.logwRef()=1.6; sd.wfRef() = wfOld;

    NiupNidnSample niupNidnSample(halfL);
    niupNidnSample.logw=complex<double>(1.2,1.5);
    niupNidnSample.diag00=diag00; niupNidnSample.diag01=diag01;
    niupNidnSample.diag10=diag10; niupNidnSample.diag11=diag11;

    NiupNidnSampleSDOperation niupNidnSampleSDOperation;
    niupNidnSampleSDOperation.applyToRight(niupNidnSample, sd, sdNew);

    EXPECT_FALSE( diff(wfRightNew, sdNew.getWf(), 1e-12) );
    EXPECT_COMPLEXDOUBLE_EQ( complex<double>(2.8,1.5), sdNew.getLogw() );
}

TEST_F(NiupNidnSDOperationTest, applyToLeft)
{
    SD sd(L,N), sdNew;
    sd.logwRef()=1.6; sd.wfRef() = wfOld;

    NiupNidnSample niupNidnSample(halfL);
    niupNidnSample.logw=complex<double>(1.2,1.5);
    niupNidnSample.diag00=diag00; niupNidnSample.diag01=diag01;
    niupNidnSample.diag10=diag10; niupNidnSample.diag11=diag11;

    NiupNidnSampleSDOperation niupNidnSampleSDOperation;
    niupNidnSampleSDOperation.applyToLeft(niupNidnSample, sd, sdNew);

    EXPECT_FALSE( diff(wfLeftNew, sdNew.getWf(), 1e-12) );
    EXPECT_COMPLEXDOUBLE_EQ( complex<double>(2.8,-1.5), sdNew.getLogw() );
}