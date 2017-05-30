//
// Created by boruoshihao on 12/28/16.
//

#include "../include/hopSDOperation.h"
#include "../../../../../common/testHao/gtest_custom.h"

using namespace std;
using namespace tensor_hao;

class HopSDOperationTest: public ::testing::Test
{
 public:
    size_t L, N;
    TensorHao<complex<double>,2> matrix, wfOld, wfRightNew, wfLeftNew;

    HopSDOperationTest( )
    {
        L=10; N=5;
        matrix.resize(L,L); wfOld.resize(L,N); wfRightNew.resize(L,N); wfLeftNew.resize(L,N);

        randomFill(matrix); randomFill(wfOld);
        gmm_cpu(matrix, wfOld, wfRightNew);
        gmm_cpu(matrix, wfOld, wfLeftNew,'C');
    }

    ~HopSDOperationTest( )  {}
};

TEST_F(HopSDOperationTest, applyToRight)
{
    SD sd(L,N), sdNew;
    Hop hop; hop.logw=complex<double>(1.2,1.5); hop.matrix=matrix;
    sd.logwRef()=1.6; sd.wfRef() = wfOld;
    HopSDOperation hopSDOperation; hopSDOperation.applyToRight(hop, sd, sdNew);

    EXPECT_FALSE( diff(wfRightNew, sdNew.getWf(), 1e-12) );
    EXPECT_COMPLEXDOUBLE_EQ( complex<double>(2.8, 1.5), sdNew.getLogw() );
}

TEST_F(HopSDOperationTest, applyToLeft)
{
    SD sd(L,N), sdNew;
    Hop hop; hop.logw=complex<double>(1.2,1.5); hop.matrix=matrix;
    sd.logwRef()=1.6; sd.wfRef() = wfOld;
    HopSDOperation hopSDOperation; hopSDOperation.applyToLeft(hop, sd, sdNew);

    EXPECT_FALSE( diff(wfLeftNew, sdNew.getWf(), 1e-12) );
    EXPECT_COMPLEXDOUBLE_EQ( complex<double>(2.8, -1.5), sdNew.getLogw() );
}