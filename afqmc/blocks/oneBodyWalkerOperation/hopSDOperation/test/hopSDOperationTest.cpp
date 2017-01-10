//
// Created by boruoshihao on 12/28/16.
//

#include "../include/hopSDOperation.h"
#include "../../../../../common/testHao/gtest_custom.h"

using namespace std;
using namespace tensor_hao;

TEST(hopSDOperationTest, applyOneBodyToRightWalker)
{
    size_t L(10), N(5);
    TensorHao<complex<double>, 2> matrix(L,L), wf(L,N), wfNew(L,N);
    randomFill(matrix); randomFill(wf);
    gmm_cpu(matrix, wf, wfNew);

    SD sd(L,N), sdNew;
    Hop hop; hop.logw=complex<double>(1.2,1.5); hop.matrix=matrix;
    sd.logwRef()=1.6; sd.wfRef() = wf;
    applyOneBodyToRightWalker(sd, sdNew, hop);

    EXPECT_FALSE( diff(wfNew, sdNew.getWf(), 1e-12) );
    EXPECT_COMPLEXDOUBLE_EQ( complex<double>(2.8, 1.5), sdNew.getLogw() );
}

TEST(hopSDOperationTest, applyOneBodyToLeftWalker)
{
    size_t L(10), N(5);
    TensorHao<complex<double>, 2> matrix(L,L), wf(L,N), wfNew(L,N);
    randomFill(matrix); randomFill(wf);
    gmm_cpu(matrix, wf, wfNew,'C');

    SD sd(L,N), sdNew;
    Hop hop; hop.logw= complex<double>(1.2,1.5); hop.matrix=matrix;
    sd.logwRef()=1.6; sd.wfRef() = wf;
    applyOneBodyToLeftWalker(sd, sdNew, hop);

    EXPECT_FALSE( diff(wfNew, sdNew.getWf(), 1e-12) );
    EXPECT_COMPLEXDOUBLE_EQ( complex<double>(2.8, -1.5), sdNew.getLogw() );
}