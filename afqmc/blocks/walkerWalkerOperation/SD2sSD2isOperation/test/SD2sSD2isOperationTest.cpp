//
// Created by boruoshihao on 5/22/17.
//
#include "../include/SD2sSD2isOperation.h"
#include "../../../../../common/testHao/gtest_custom.h"

using namespace std;
using namespace tensor_hao;

class SD2sSD2isOperationTest: public ::testing::Test
{
 public:
    size_t L, Nup, Ndn;
    TensorHao<complex<double>,2> wfLeftUp, wfLeftDn, wfRightUp, wfRightDn;
    SD2s walkerLeft;
    SD2is walkerRight;

    SD2sSD2isOperationTest( )
    {
        L=10; Nup=3; Ndn=5;

        wfLeftUp.resize(L,Nup); wfLeftDn.resize(L,Ndn); wfRightUp.resize(L,Nup); wfRightDn.resize(L,Ndn);
        randomFill(wfLeftUp); randomFill(wfLeftDn); randomFill(wfRightDn);
        for (size_t i = 0; i < Nup; ++i)
        {
            for (size_t j = 0; j < L; ++j) wfRightUp(j,i)=wfRightDn(j,i);
        }

        walkerLeft.resize(L, Nup, Ndn);
        walkerLeft.logwRef() = complex<double>(1.2, 2.0);
        walkerLeft.wfUpRef() = wfLeftUp;
        walkerLeft.wfDnRef() = wfLeftDn;

        walkerRight.resize(L, Nup, Ndn);
        walkerRight.logwRef() = complex<double>(2.2, 3.0);
        walkerRight.wfRef() = wfRightDn;
    }

    ~SD2sSD2isOperationTest( )  {}
};

TEST_F(SD2sSD2isOperationTest, voidConstruction)
{
    SD2sSD2isOperation sd2sSD2isOperation;
    EXPECT_EQ( sd2sSD2isOperation.getState(), SD2sSD2isOperationState::VOID );
    EXPECT_FALSE( sd2sSD2isOperation.getWalkerLeft() );
    EXPECT_FALSE( sd2sSD2isOperation.getWalkerRight() );
}

TEST_F(SD2sSD2isOperationTest, walkerPointerConstruction)
{
    SD2sSD2isOperation sd2sSD2isOperation(walkerLeft, walkerRight);

    EXPECT_EQ( sd2sSD2isOperation.getState(), SD2sSD2isOperationState::VOID );
    EXPECT_TRUE( sd2sSD2isOperation.getWalkerLeft() );
    EXPECT_TRUE( sd2sSD2isOperation.getWalkerRight() );
}

TEST_F(SD2sSD2isOperationTest, reset)
{
    SD2sSD2isOperation sd2sSD2isOperation(walkerLeft, walkerRight);

    EXPECT_EQ( sd2sSD2isOperation.getState(), SD2sSD2isOperationState::VOID );
    sd2sSD2isOperation.returnLUOverlapUp();
    EXPECT_EQ( sd2sSD2isOperation.getState(), SD2sSD2isOperationState::LUOVERLAP );
    sd2sSD2isOperation.returnLUOverlapDn();
    EXPECT_EQ( sd2sSD2isOperation.getState(), SD2sSD2isOperationState::LUOVERLAP );
    sd2sSD2isOperation.returnThetaUp_T();
    EXPECT_EQ( sd2sSD2isOperation.getState(), SD2sSD2isOperationState::THETA_T );
    sd2sSD2isOperation.returnThetaDn_T();
    EXPECT_EQ( sd2sSD2isOperation.getState(), SD2sSD2isOperationState::THETA_T );
    sd2sSD2isOperation.reSet();
    EXPECT_EQ( sd2sSD2isOperation.getState(), SD2sSD2isOperationState::VOID );
}

TEST_F(SD2sSD2isOperationTest, getLogOverlap)
{
    complex<double> logOverlap = complex<double>(1.2, -2.0) + complex<double>(2.2, 3.0);
    TensorHao< complex<double>,2 > ovlpUp(Nup,Nup); gmm_cpu(wfLeftUp, wfRightUp, ovlpUp, 'C');
    TensorHao< complex<double>,2 > ovlpDn(Ndn,Ndn); gmm_cpu(wfLeftDn, wfRightDn, ovlpDn, 'C');
    logOverlap += logDeterminant( LUconstruct_cpu(ovlpUp) )+logDeterminant( LUconstruct_cpu(ovlpDn) );

    SD2sSD2isOperation sd2sSD2isOperation(walkerLeft, walkerRight);
    EXPECT_COMPLEXDOUBLE_EQ( logOverlap, sd2sSD2isOperation.returnLogOverlap()  );
}

TEST_F(SD2sSD2isOperationTest, returnGreenMatrixAndDiagonalUp)
{
    TensorHao< complex<double>,2 > ovlpUp(Nup,Nup), wfLeftUpDagger(Nup,L), greenMatrixUp(L,L);
    gmm_cpu(wfLeftUp, wfRightUp, ovlpUp, 'C');
    ovlpUp = inverse_cpu(  LUconstruct_cpu( move(ovlpUp) ) );
    gmm_cpu( ovlpUp, wfLeftUp, wfLeftUpDagger, 'N', 'C' );
    gmm_cpu( wfRightUp, wfLeftUpDagger, greenMatrixUp );
    greenMatrixUp = trans( greenMatrixUp );

    TensorHao< complex<double>,1 > greenDiagonalUp(L);
    for (size_t i = 0; i < L; ++i) greenDiagonalUp(i) = greenMatrixUp(i,i);

    SD2sSD2isOperation sd2sSD2isOperation(walkerLeft, walkerRight);
    EXPECT_FALSE( diff(greenMatrixUp, sd2sSD2isOperation.returnGreenMatrixUp(), 1e-12) );
    EXPECT_FALSE( diff(greenDiagonalUp, sd2sSD2isOperation.returnGreenDiagonalUp(), 1e-12) );

}

TEST_F(SD2sSD2isOperationTest, returnGreenMatrixAndDiagonalDn)
{
    TensorHao< complex<double>,2 > ovlpDn(Ndn,Ndn),  wfLeftDnDagger(Ndn,L), greenMatrixDn(L,L);
    gmm_cpu(wfLeftDn, wfRightDn, ovlpDn, 'C');
    ovlpDn = inverse_cpu(  LUconstruct_cpu( move(ovlpDn) ) );
    gmm_cpu( ovlpDn, wfLeftDn, wfLeftDnDagger, 'N', 'C' );
    gmm_cpu( wfRightDn, wfLeftDnDagger, greenMatrixDn );
    greenMatrixDn = trans( greenMatrixDn );

    TensorHao< complex<double>,1 > greenDiagonalDn(L);
    for (size_t i = 0; i < L; ++i) greenDiagonalDn(i) = greenMatrixDn(i,i);

    SD2sSD2isOperation sd2sSD2isOperation(walkerLeft, walkerRight);
    EXPECT_FALSE( diff(greenMatrixDn, sd2sSD2isOperation.returnGreenMatrixDn(), 1e-12) );
    EXPECT_FALSE( diff(greenDiagonalDn, sd2sSD2isOperation.returnGreenDiagonalDn(), 1e-12) );
}