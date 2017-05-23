//
// Created by boruoshihao on 1/10/17.
//

#include "../include/SDSDOperation.h"
#include "../../../../../common/testHao/gtest_custom.h"

using namespace std;
using namespace tensor_hao;

TEST(SDSDOperationTest, voidConstruction)
{
    SDSDOperation sdOperation;

    EXPECT_EQ( sdOperation.getState(), SDOperationState::VOID );
    EXPECT_FALSE( sdOperation.getWalkerLeft() );
    EXPECT_FALSE( sdOperation.getWalkerRight() );
}

TEST(SDSDOperationTest, walkerPointerConstruction)
{
    SD walkerLeft, walkerRight;
    SDSDOperation sdOperation(walkerLeft, walkerRight);

    EXPECT_EQ( sdOperation.getState(), SDOperationState::VOID );
    EXPECT_TRUE( sdOperation.getWalkerLeft() );
    EXPECT_TRUE( sdOperation.getWalkerRight() );
}

TEST(SDSDOperationTest, reSet)
{
    size_t L(10), N(5);
    SD walkerLeft(L,N), walkerRight(L,N);
    randomFill( walkerLeft.wfRef() ); randomFill( walkerRight.wfRef() );

    SDSDOperation sdOperation(walkerLeft, walkerRight);
    sdOperation.returnLUOverlap();
    EXPECT_EQ( sdOperation.getState(), SDOperationState::LUOVERLAP );
    sdOperation.returnWfLeftDagger();
    EXPECT_EQ( sdOperation.getState(), SDOperationState::WFLEFTDAGGER );
    sdOperation.reSet();
    EXPECT_EQ( sdOperation.getState(), SDOperationState::VOID );
}

TEST(SDSDOperationTest, getLogOverlap)
{
    size_t L(10), N(5);
    SD walkerLeft(L,N), walkerRight(L,N);
    walkerLeft.logwRef()  = complex<double>(2.0, 3.0); randomFill( walkerLeft.wfRef() );
    walkerRight.logwRef() = complex<double>(1.0, 5.0); randomFill( walkerRight.wfRef() );

    TensorHao< complex<double>,2 > ovlp(N,N);
    gmm_cpu(walkerLeft.getWf(), walkerRight.getWf(), ovlp, 'C');
    complex<double> logOverlap = logDeterminant( LUconstruct_cpu(ovlp) ) + complex<double>(3.0, 2.0);

    SDSDOperation sdOperation(walkerLeft, walkerRight);

    EXPECT_COMPLEXDOUBLE_EQ( logOverlap, sdOperation.returnLogOverlap()  );
}

TEST(SDSDOperationTest, getGreenMatrix)
{
    size_t L(10), N(5);
    SD walkerLeft(L,N), walkerRight(L,N);
    walkerLeft.logwRef()  = complex<double>(2.0, 3.0); randomFill( walkerLeft.wfRef() );
    walkerRight.logwRef() = complex<double>(1.0, 5.0); randomFill( walkerRight.wfRef() );

    SDSDOperation sdOperation(walkerLeft, walkerRight);
    TensorHao<complex<double>, 2> greenMatrix = sdOperation.returnGreenMatrix();

    TensorHao<complex<double>, 2> ovlp(N,N), wfLeftDagger(N,L), greenMatrixExact(L,L);
    gmm_cpu(walkerLeft.getWf(), walkerRight.getWf(), ovlp, 'C');
    ovlp = inverse_cpu(  LUconstruct_cpu( move(ovlp) ) );
    gmm_cpu( ovlp, conjtrans( walkerLeft.getWf() ), wfLeftDagger );
    gmm_cpu( walkerRight.getWf(), wfLeftDagger, greenMatrixExact );
    greenMatrixExact = trans( greenMatrixExact );

    EXPECT_FALSE( diff(greenMatrix, greenMatrixExact, 1e-12) );
}

TEST(SDSDOperationTest, getGreenDiagonal)
{
    size_t L(10), N(5);
    SD walkerLeft(L,N), walkerRight(L,N);
    walkerLeft.logwRef()  = complex<double>(2.0, 3.0); randomFill( walkerLeft.wfRef() );
    walkerRight.logwRef() = complex<double>(1.0, 5.0); randomFill( walkerRight.wfRef() );

    SDSDOperation sdOperation(walkerLeft, walkerRight);
    TensorHao<complex<double>, 1> greenDiagonal = sdOperation.returnGreenDiagonal();

    TensorHao<complex<double>, 2> ovlp(N,N), wfLeftDagger(N,L), greenMatrixExact(L,L);
    gmm_cpu(walkerLeft.getWf(), walkerRight.getWf(), ovlp, 'C');
    ovlp = inverse_cpu(  LUconstruct_cpu( move(ovlp) ) );
    gmm_cpu( ovlp, walkerLeft.getWf(), wfLeftDagger, 'N', 'C' );
    gmm_cpu( walkerRight.getWf(), wfLeftDagger, greenMatrixExact );
    greenMatrixExact = trans( greenMatrixExact );

    TensorHao<complex<double>, 1> greenDiagonalExact(L);
    for(size_t i = 0; i < L; ++i) greenDiagonalExact(i) = greenMatrixExact(i,i);

    EXPECT_FALSE( diff(greenDiagonal, greenDiagonalExact, 1e-12) );
}

TEST(SDSDOperationTest, getGreenOffDiagonal)
{
    size_t L(10), N(5);
    SD walkerLeft(L,N), walkerRight(L,N);
    walkerLeft.logwRef()  = complex<double>(2.0, 3.0); randomFill( walkerLeft.wfRef() );
    walkerRight.logwRef() = complex<double>(1.0, 5.0); randomFill( walkerRight.wfRef() );

    SDSDOperation sdOperation(walkerLeft, walkerRight);
    TensorHao<complex<double>, 1> greenOffDiagonal = sdOperation.returnGreenOffDiagonal();

    TensorHao<complex<double>, 2> ovlp(N,N), wfLeftDagger(N,L), greenMatrixExact(L,L);
    gmm_cpu(walkerLeft.getWf(), walkerRight.getWf(), ovlp, 'C');
    ovlp = inverse_cpu(  LUconstruct_cpu( move(ovlp) ) );
    gmm_cpu( ovlp, conjtrans( walkerLeft.getWf() ), wfLeftDagger );
    gmm_cpu( walkerRight.getWf(), wfLeftDagger, greenMatrixExact );
    greenMatrixExact = trans( greenMatrixExact );

    TensorHao<complex<double>, 1> greenOffDiagonalExact(L);
    for(size_t i = 0; i < L/2; ++i) greenOffDiagonalExact(i)     = greenMatrixExact(i,i+L/2);
    for(size_t i = 0; i < L/2; ++i) greenOffDiagonalExact(i+L/2) = greenMatrixExact(i+L/2,i);

    EXPECT_FALSE( diff(greenOffDiagonal, greenOffDiagonalExact, 1e-12) );
}