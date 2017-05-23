//
// Created by boruoshihao on 1/10/17.
//

#include "../include/SDSDOperation.h"
#include "../../../../../common/testHao/gtest_custom.h"

using namespace std;
using namespace tensor_hao;

class SDSDOperationTest: public ::testing::Test
{
 public:
    size_t L, N;
    TensorHao<complex<double>,2> wfLeft,wfRight;
    SD walkerLeft, walkerRight;

    SDSDOperationTest( )
    {
        L=10; N=5;

        wfLeft.resize(L,N); wfRight.resize(L,N);
        randomFill(wfLeft); randomFill(wfRight);

        walkerLeft.resize(L, N);
        walkerLeft.logwRef() = complex<double>(2.0, 3.0);
        walkerLeft.wfRef() = wfLeft;

        walkerRight.resize(L, N);
        walkerRight.logwRef() = complex<double>(1.0, 5.0);
        walkerRight.wfRef() = wfRight;
    }

    ~SDSDOperationTest( )  {}
};

TEST_F(SDSDOperationTest, voidConstruction)
{
    SDSDOperation sdOperation;

    EXPECT_EQ( sdOperation.getState(), SDSDOperationState::VOID );
    EXPECT_FALSE( sdOperation.getWalkerLeft() );
    EXPECT_FALSE( sdOperation.getWalkerRight() );
}

TEST_F(SDSDOperationTest, walkerPointerConstruction)
{
    SDSDOperation sdOperation(walkerLeft, walkerRight);

    EXPECT_EQ( sdOperation.getState(), SDSDOperationState::VOID );
    EXPECT_TRUE( sdOperation.getWalkerLeft() );
    EXPECT_TRUE( sdOperation.getWalkerRight() );
}

TEST_F(SDSDOperationTest, reSet)
{
    SDSDOperation sdOperation(walkerLeft, walkerRight);

    EXPECT_EQ( sdOperation.getState(), SDSDOperationState::VOID );
    sdOperation.returnLUOverlap();
    EXPECT_EQ( sdOperation.getState(), SDSDOperationState::LUOVERLAP );
    sdOperation.returnTheta_T();
    EXPECT_EQ( sdOperation.getState(), SDSDOperationState::THETA_T );
    sdOperation.reSet();
    EXPECT_EQ( sdOperation.getState(), SDSDOperationState::VOID );
}

TEST_F(SDSDOperationTest, getLogOverlap)
{
    TensorHao< complex<double>,2 > ovlp(N,N);
    gmm_cpu(wfLeft, wfRight, ovlp, 'C');
    complex<double> logOverlap = logDeterminant( LUconstruct_cpu(ovlp) ) + complex<double>(3.0, 2.0);

    SDSDOperation sdOperation(walkerLeft, walkerRight);
    EXPECT_COMPLEXDOUBLE_EQ( logOverlap, sdOperation.returnLogOverlap()  );
}

TEST_F(SDSDOperationTest, getGreenMatrixDiagonalAndOffDiagonal)
{
    TensorHao<complex<double>, 2> ovlp(N,N), wfLeftDagger(N,L), greenMatrix(L,L);
    gmm_cpu(wfLeft, wfRight, ovlp, 'C');
    ovlp = inverse_cpu(  LUconstruct_cpu( move(ovlp) ) );
    gmm_cpu( ovlp, wfLeft, wfLeftDagger, 'N', 'C' );
    gmm_cpu( wfRight, wfLeftDagger, greenMatrix );
    greenMatrix = trans( greenMatrix );

    SDSDOperation sdOperation(walkerLeft, walkerRight);
    EXPECT_FALSE( diff(greenMatrix, sdOperation.returnGreenMatrix(), 1e-12) );

    TensorHao<complex<double>, 1> greenDiagonal(L);
    for(size_t i = 0; i < L; ++i) greenDiagonal(i) = greenMatrix(i,i);
    EXPECT_FALSE( diff(greenDiagonal, sdOperation.returnGreenDiagonal(), 1e-12) );

    TensorHao<complex<double>, 1> greenOffDiagonal(L);
    for(size_t i = 0; i < L/2; ++i) greenOffDiagonal(i)     = greenMatrix(i,i+L/2);
    for(size_t i = 0; i < L/2; ++i) greenOffDiagonal(i+L/2) = greenMatrix(i+L/2,i);
    EXPECT_FALSE( diff(greenOffDiagonal, sdOperation.returnGreenOffDiagonal(), 1e-12) );
}