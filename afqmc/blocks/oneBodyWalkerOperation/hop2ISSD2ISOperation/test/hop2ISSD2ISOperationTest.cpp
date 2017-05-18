//
// Created by boruoshihao on 12/28/16.
//

#include "../include/hop2ISSD2ISOperation.h"
#include "../../../../../common/testHao/gtest_custom.h"

using namespace std;
using namespace tensor_hao;

TEST(hop2ISSD2ISOperationTest, applyOneBodyToRightWalker)
{
    size_t L(10), Nup(5), Ndn(3);
    TensorHao<complex<double>, 2> matrix(L,L), wf( L, max(Nup, Ndn) ), wfNew( L, max(Nup, Ndn) );
    randomFill(matrix); randomFill(wf);
    gmm_cpu(matrix, wf, wfNew);

    SD2IS sd2IS(L,Nup, Ndn), sd2ISNew;
    Hop2IS hop2IS; hop2IS.logw=complex<double>(1.2,1.5); hop2IS.matrix=matrix;
    sd2IS.logwRef()=1.6; sd2IS.wfRef() = wf;
    applyOneBodyToRightWalker(sd2IS, sd2ISNew, hop2IS);

    EXPECT_FALSE( diff(wfNew, sd2ISNew.getWf(), 1e-12) );
    EXPECT_COMPLEXDOUBLE_EQ( complex<double>(2.8, 1.5), sd2ISNew.getLogw() );
    EXPECT_EQ( L, sd2ISNew.getL() );
    EXPECT_EQ( Nup, sd2ISNew.getNup() );
    EXPECT_EQ( Ndn, sd2ISNew.getNdn() );
}

TEST(hop2ISSD2ISOperationTest, applyOneBodyToLeftWalker)
{
    size_t L(10), Nup(5), Ndn(3);
    TensorHao<complex<double>, 2> matrix(L,L), wf( L, max(Nup, Ndn) ), wfNew( L, max(Nup, Ndn) );
    randomFill(matrix); randomFill(wf);
    gmm_cpu(matrix, wf, wfNew,'C');

    SD2IS sd2IS(L,Nup, Ndn), sd2ISNew;
    Hop2IS hop2IS; hop2IS.logw= complex<double>(1.2,1.5); hop2IS.matrix=matrix;
    sd2IS.logwRef()=1.6; sd2IS.wfRef() = wf;
    applyOneBodyToLeftWalker(sd2IS, sd2ISNew, hop2IS);

    EXPECT_FALSE( diff(wfNew, sd2ISNew.getWf(), 1e-12) );
    EXPECT_COMPLEXDOUBLE_EQ( complex<double>(2.8, -1.5), sd2ISNew.getLogw() );
    EXPECT_EQ( L, sd2ISNew.getL() );
    EXPECT_EQ( Nup, sd2ISNew.getNup() );
    EXPECT_EQ( Ndn, sd2ISNew.getNdn() );
}