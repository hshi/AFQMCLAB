//
// Created by boruoshihao on 12/28/16.
//

#include "../include/hop2isSD2isOperation.h"
#include "../../../../../common/testHao/gtest_custom.h"

using namespace std;
using namespace tensor_hao;

TEST(hop2isSD2isOperationTest, applyOneBodyToRightWalker)
{
    size_t L(10), Nup(5), Ndn(3);
    TensorHao<complex<double>, 2> matrix(L,L), wf( L, max(Nup, Ndn) ), wfNew( L, max(Nup, Ndn) );
    randomFill(matrix); randomFill(wf);
    gmm_cpu(matrix, wf, wfNew);

    SD2is sd2is(L,Nup, Ndn), sd2isNew;
    Hop2is hop2is; hop2is.logw=complex<double>(1.2,1.5); hop2is.matrix=matrix;
    sd2is.logwRef()=1.6; sd2is.wfRef() = wf;
    applyOneBodyToRightWalker(sd2is, sd2isNew, hop2is);

    EXPECT_FALSE( diff(wfNew, sd2isNew.getWf(), 1e-12) );
    EXPECT_COMPLEXDOUBLE_EQ( complex<double>(2.8, 1.5), sd2isNew.getLogw() );
    EXPECT_EQ( L, sd2isNew.getL() );
    EXPECT_EQ( Nup, sd2isNew.getNup() );
    EXPECT_EQ( Ndn, sd2isNew.getNdn() );
}

TEST(hop2isSD2isOperationTest, applyOneBodyToLeftWalker)
{
    size_t L(10), Nup(5), Ndn(3);
    TensorHao<complex<double>, 2> matrix(L,L), wf( L, max(Nup, Ndn) ), wfNew( L, max(Nup, Ndn) );
    randomFill(matrix); randomFill(wf);
    gmm_cpu(matrix, wf, wfNew,'C');

    SD2is sd2is(L,Nup, Ndn), sd2isNew;
    Hop2is hop2is; hop2is.logw= complex<double>(1.2,1.5); hop2is.matrix=matrix;
    sd2is.logwRef()=1.6; sd2is.wfRef() = wf;
    applyOneBodyToLeftWalker(sd2is, sd2isNew, hop2is);

    EXPECT_FALSE( diff(wfNew, sd2isNew.getWf(), 1e-12) );
    EXPECT_COMPLEXDOUBLE_EQ( complex<double>(2.8, -1.5), sd2isNew.getLogw() );
    EXPECT_EQ( L, sd2isNew.getL() );
    EXPECT_EQ( Nup, sd2isNew.getNup() );
    EXPECT_EQ( Ndn, sd2isNew.getNdn() );
}
