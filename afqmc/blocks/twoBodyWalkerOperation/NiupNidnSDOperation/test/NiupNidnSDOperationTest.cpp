//
// Created by boruoshihao on 1/10/17.
//

#include "../include/NiupNidnSDOperation.h"
#include "../../../../../common/testHao/gtest_custom.h"

using namespace std;
using namespace tensor_hao;

TEST(NiupNidnSDOperationTest, applyTwoBodySampleToRightWalker)
{
    size_t L(10), N(6), halfL(L/2);
    TensorHao<complex<double>, 2> matrix(L,L), wf(L,N), wfNew(L,N);
    TensorHao<complex<double>, 1> diag00(halfL), diag10(halfL), diag01(halfL), diag11(halfL);

    randomFill(diag00); randomFill(diag01);
    randomFill(diag10); randomFill(diag11);

    matrix = complex<double>(0,0);
    for(size_t i = 0; i < halfL; ++i)
    {
        matrix(i,i)       = diag00(i); matrix(i, i+halfL)       = diag01(i);
        matrix(i+halfL,i) = diag10(i); matrix(i+halfL, i+halfL) = diag11(i);
    }
    randomFill(wf);
    gmm_cpu(matrix, wf, wfNew);

    SD sd(L,N), sdNew;
    sd.logwRef()=1.6; sd.wfRef() = wf;

    NiupNidnSample niupNidnSample(halfL);
    niupNidnSample.logw=complex<double>(1.2,1.5);
    niupNidnSample.diag00=diag00; niupNidnSample.diag01=diag01;
    niupNidnSample.diag10=diag10; niupNidnSample.diag11=diag11;

    applyTwoBodySampleToRightWalker(sd, sdNew, niupNidnSample);

    EXPECT_FALSE( diff(wfNew, sdNew.getWf(), 1e-12) );
    EXPECT_COMPLEXDOUBLE_EQ( complex<double>(2.8,1.5), sdNew.getLogw() );
}

TEST(NiupNidnSDOperationTest, applyTwoBodySampleToLeftWalker)
{
    size_t L(10), N(6), halfL(L/2);
    TensorHao<complex<double>, 2> matrix(L,L), wf(L,N), wfNew(L,N);
    TensorHao<complex<double>, 1> diag00(halfL), diag10(halfL), diag01(halfL), diag11(halfL);

    randomFill(diag00); randomFill(diag01);
    randomFill(diag10); randomFill(diag11);

    matrix = complex<double>(0,0);
    for(size_t i = 0; i < halfL; ++i)
    {
        matrix(i,i)       = diag00(i); matrix(i, i+halfL)       = diag01(i);
        matrix(i+halfL,i) = diag10(i); matrix(i+halfL, i+halfL) = diag11(i);
    }
    randomFill(wf);
    gmm_cpu(matrix, wf, wfNew,'C');

    SD sd(L,N), sdNew;
    sd.logwRef()=1.6; sd.wfRef() = wf;

    NiupNidnSample niupNidnSample(halfL);
    niupNidnSample.logw=complex<double>(1.2,1.5);
    niupNidnSample.diag00=diag00; niupNidnSample.diag01=diag01;
    niupNidnSample.diag10=diag10; niupNidnSample.diag11=diag11;

    applyTwoBodySampleToLeftWalker(sd, sdNew, niupNidnSample);

    EXPECT_FALSE( diff(wfNew, sdNew.getWf(), 1e-12) );
    EXPECT_COMPLEXDOUBLE_EQ( complex<double>(2.8,-1.5), sdNew.getLogw() );
}