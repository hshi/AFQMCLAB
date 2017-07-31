//
// Created by boruoshihao on 5/19/17.
//
#include "../include/logHop2isSD2isOperation.h"
#include "../../../../../common/testHao/gtest_custom.h"

using namespace std;
using namespace tensor_hao;

class LogHop2isSD2isOperationTest: public ::testing::Test
{
 public:
    size_t L, Nup, Ndn;
    TensorHao<complex<double>,2> matrix, wfOld, wfRightNew, wfLeftNew;


    LogHop2isSD2isOperationTest( )
    {
        L=3; Nup=1; Ndn=2;
        matrix.resize(L,L);
        wfOld.resize(L, Ndn);
        wfRightNew.resize(L, Ndn);
        wfLeftNew.resize(L, Ndn);

        matrix = {
                   {2,  3}, {4,   2}, {1,   1},
                   {1, -1}, {0, 0.3}, {1,  -1},
                   {3,  2}, {2,   3}, {0, 0.5}
                 };
        matrix = complex<double>(-0.01, 0.0) * matrix;

        wfOld = { {1, 0}, {2,0}, {3, 0}, {3,0}, {4,0}, {5, 0} };

        wfRightNew = { {0.8717255743431891,-0.06695756061260984}, {1.9019539751922434,-0.11272541520548454}, {2.9713563453236675, -0.0038676809054978764},
                       {2.753351116138562, -0.14393925193667553}, {3.7836486105153155,-0.21511811236274694}, {4.932649990968739, -0.012861814634312912} };
        wfLeftNew  = { {0.8708226627963166, 0.09656591603485742}, {1.961995737773784, -0.034019035572233965},{2.9316294741182647, 0.09182786294989435},
                       {2.7315235332357157, 0.21256279549696155}, {3.924363675467334, -0.0680085413131974},  {4.833174488748831, 0.19818901143889675} };

    }

    ~LogHop2isSD2isOperationTest( )  {}
};


TEST_F(LogHop2isSD2isOperationTest, fixedOrderNumber)
{
    SD2is sd2is(L,Nup, Ndn), sd2isRightNew, sd2isLeftNew;
    LogHop2is logHop2is; logHop2is.logw=complex<double>(1.2,1.5); logHop2is.matrix=matrix;
    sd2is.logwRef()=1.6; sd2is.wfRef() = wfOld;

    LogHop2isSD2isOperation oneBodyWalkerOperation("fixedOrder", 8, 1e-8);

    oneBodyWalkerOperation.applyToRight(logHop2is, sd2is, sd2isRightNew);
    EXPECT_EQ( static_cast<size_t>(8), oneBodyWalkerOperation.getCurrentOrder() );
    EXPECT_FALSE( diff(wfRightNew, sd2isRightNew.getWf(), 1e-12) );

    oneBodyWalkerOperation.applyToLeft(logHop2is, sd2is, sd2isLeftNew);
    EXPECT_EQ( static_cast<size_t>(8), oneBodyWalkerOperation.getCurrentOrder() );
    EXPECT_FALSE( diff(wfLeftNew, sd2isLeftNew.getWf(), 1e-12) );
}

TEST_F(LogHop2isSD2isOperationTest, fixedOrderAcuracy)
{
    SD2is sd2is(L,Nup, Ndn), sd2isRightNew, sd2isLeftNew;
    LogHop2is logHop2is; logHop2is.logw=complex<double>(1.2,1.5); logHop2is.matrix=matrix;
    sd2is.logwRef()=1.6; sd2is.wfRef() = wfOld;

    LogHop2isSD2isOperation oneBodyWalkerOperation("fixedOrder", 0, 1e-8);

    oneBodyWalkerOperation.applyToRight(logHop2is, sd2is, sd2isRightNew);
    EXPECT_EQ( static_cast<size_t>(6), oneBodyWalkerOperation.getCurrentOrder() );
    EXPECT_FALSE( diff(wfRightNew, sd2isRightNew.getWf(), 1e-8) );

    oneBodyWalkerOperation.applyToLeft(logHop2is, sd2is, sd2isLeftNew);
    EXPECT_EQ( static_cast<size_t>(6), oneBodyWalkerOperation.getCurrentOrder() );
    EXPECT_FALSE( diff(wfLeftNew, sd2isLeftNew.getWf(), 1e-8) );
}

TEST_F(LogHop2isSD2isOperationTest, dynamicOrder)
{
    SD2is sd2is(L,Nup, Ndn), sd2isRightNew, sd2isLeftNew;
    LogHop2is logHop2is; logHop2is.logw=complex<double>(1.2,1.5); logHop2is.matrix=matrix;
    sd2is.logwRef()=1.6; sd2is.wfRef() = wfOld;

    LogHop2isSD2isOperation oneBodyWalkerOperation("dynamicOrder", 0, 1e-8);

    oneBodyWalkerOperation.applyToRight(logHop2is, sd2is, sd2isRightNew);
    EXPECT_EQ( static_cast<size_t>(6), oneBodyWalkerOperation.getCurrentOrder() );
    EXPECT_FALSE( diff(wfRightNew, sd2isRightNew.getWf(), 1e-8) );

    oneBodyWalkerOperation.applyToLeft(logHop2is, sd2is, sd2isLeftNew);
    EXPECT_EQ( static_cast<size_t>(6), oneBodyWalkerOperation.getCurrentOrder() );
    EXPECT_FALSE( diff(wfLeftNew, sd2isLeftNew.getWf(), 1e-8) );
}
