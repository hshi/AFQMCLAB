//
// Created by boruoshihao on 12/28/16.
//

#include "../include/hop2isSD2isOperation.h"
#include "../../../../../common/testHao/gtest_custom.h"

using namespace std;
using namespace tensor_hao;

class Hop2isSD2isOperationTest: public ::testing::Test
{
 public:
    size_t L, Nup, Ndn;
    TensorHao<complex<double>,2> matrix, wfOld, wfRightNew, wfLeftNew;

    Hop2isSD2isOperationTest( )
    {
        L=10; Nup=5; Ndn=3;
        matrix.resize(L,L);
        wfOld.resize( L, max(Nup, Ndn) );
        wfRightNew.resize( L, max(Nup, Ndn) );
        wfLeftNew.resize( L, max(Nup, Ndn) );

        randomFill(matrix); randomFill(wfOld);
        gmm_cpu(matrix, wfOld, wfRightNew);
        gmm_cpu(matrix, wfOld, wfLeftNew,'C');
    }

    ~Hop2isSD2isOperationTest( )  {}
};

TEST_F(Hop2isSD2isOperationTest, applyToRight)
{
    SD2is sd2is(L,Nup, Ndn), sd2isNew;
    Hop2is hop2is; hop2is.logw=complex<double>(1.2,1.5); hop2is.matrix=matrix;
    sd2is.logwRef()=1.6; sd2is.wfRef() = wfOld;

    Hop2isSD2isOperation hop2isSD2isOperation;
    hop2isSD2isOperation.applyToRight(hop2is, sd2is, sd2isNew);

    EXPECT_FALSE( diff(wfRightNew, sd2isNew.getWf(), 1e-12) );
    EXPECT_COMPLEXDOUBLE_EQ( complex<double>(2.8, 1.5), sd2isNew.getLogw() );
    EXPECT_EQ( L, sd2isNew.getL() );
    EXPECT_EQ( Nup, sd2isNew.getNup() );
    EXPECT_EQ( Ndn, sd2isNew.getNdn() );
}

TEST_F(Hop2isSD2isOperationTest, applyToLeft)
{
    SD2is sd2is(L,Nup, Ndn), sd2isNew;
    Hop2is hop2is; hop2is.logw=complex<double>(1.2,1.5); hop2is.matrix=matrix;
    sd2is.logwRef()=1.6; sd2is.wfRef() = wfOld;

    Hop2isSD2isOperation hop2isSD2isOperation;
    hop2isSD2isOperation.applyToLeft(hop2is, sd2is, sd2isNew);

    EXPECT_FALSE( diff(wfLeftNew, sd2isNew.getWf(), 1e-12) );
    EXPECT_COMPLEXDOUBLE_EQ( complex<double>(2.8, -1.5), sd2isNew.getLogw() );
    EXPECT_EQ( L, sd2isNew.getL() );
    EXPECT_EQ( Nup, sd2isNew.getNup() );
    EXPECT_EQ( Ndn, sd2isNew.getNdn() );
}