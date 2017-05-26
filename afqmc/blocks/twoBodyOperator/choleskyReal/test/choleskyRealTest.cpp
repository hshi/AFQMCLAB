//
// Created by boruoshihao on 5/23/17.
//

#include "../include/choleskyReal.h"
#include "../../../../../common/testHao/gtest_custom.h"

using namespace std;
using namespace tensor_hao;

#define pi 3.14159265358979324

class CholeskyRealTest: public ::testing::Test
{
 public:
    double dt;
    size_t L, choleskyNumber;
    TensorHao<double, 3> choleskyVecs;
    TensorHao<double, 1> choleskyBg;
    TensorHao<double, 1> force;

    CholeskyRealTest( )
    {
        dt = 0.01; L=10; choleskyNumber = 5;
        choleskyVecs.resize(L, L, choleskyNumber); randomFill(choleskyVecs);
        choleskyBg.resize(choleskyNumber); randomFill(choleskyBg);
        force.resize(choleskyNumber); randomFill(force);
    }

    ~CholeskyRealTest( )  {}
};

TEST_F(CholeskyRealTest, voidConstruction)
{
    CholeskyReal choleskyReal;
    EXPECT_EQ( 0.0, choleskyReal.getDt() );
    EXPECT_FALSE( choleskyReal.getCholeskyVecs() );
    EXPECT_FALSE( choleskyReal.getCholeskyBg() );
}

TEST_F(CholeskyRealTest, paramsConstruction)
{
    CholeskyReal choleskyReal(dt, choleskyVecs, choleskyBg);

    EXPECT_DOUBLE_EQ( dt, choleskyReal.getDt() );
    EXPECT_EQ( &choleskyVecs, choleskyReal.getCholeskyVecs() );
    EXPECT_EQ( &choleskyBg, choleskyReal.getCholeskyBg() );
    EXPECT_EQ( choleskyNumber, choleskyReal.getCholeskyNumber() );
    EXPECT_EQ( L, choleskyReal.returnBasisSize() );
}

TEST_F(CholeskyRealTest, sampleAuxFromForce)
{
    CholeskyReal choleskyReal(dt, choleskyVecs, choleskyBg);
    CholeskyRealAux aux = choleskyReal.sampleAuxFromForce(force);
    EXPECT_EQ( choleskyNumber, aux.size() );
}

TEST_F(CholeskyRealTest, logProbOfAuxFromForce)
{
    CholeskyReal choleskyReal(dt, choleskyVecs, choleskyBg);
    CholeskyRealAux aux = choleskyReal.sampleAuxFromForce(force);
    double logProb = choleskyReal.logProbOfAuxFromForce(aux, force);

    double prob(1.0);
    for(size_t i = 0; i < choleskyNumber; ++i)
    {
        prob *= exp( -0.5 * (aux(i)-force(i)) * (aux(i)-force(i)) ) / ( sqrt(2.0*pi) );
    }
    EXPECT_DOUBLE_EQ( prob, exp(logProb) );
}

TEST_F(CholeskyRealTest, getTwoBodySampleFromAux)
{
    CholeskyReal choleskyReal(dt, choleskyVecs, choleskyBg);
    CholeskyRealAux aux = choleskyReal.sampleAuxFromForce(force);
    CholeskyRealSample sample = choleskyReal.getTwoBodySampleFromAux(aux);

    complex<double> w(1.0); complex<double> sqrtMinusDt=sqrt( -dt*complex<double>(1.0,0.0) );
    for(size_t i = 0; i < choleskyNumber; ++i)
    {
        w *= exp( -0.5*aux(i)*aux(i) -aux(i)*sqrtMinusDt*choleskyBg(i) ) / ( sqrt(2.0*pi) );
    }
    EXPECT_COMPLEX_NEAR( w, exp(sample.logw), 1e-12 );

    TensorHao<double, 2> matrixReal(L,L); matrixReal=0.0;
    for(size_t i = 0; i < choleskyNumber; ++i)
    {
        matrixReal += aux(i) * choleskyVecs[i];
    }
    TensorHao< complex<double>, 2> matrixComplex(L,L);
    for(size_t i = 0; i <L ; ++i)
    {
        for(size_t j = 0; j < L; ++j) matrixComplex(j,i) = sqrtMinusDt * matrixReal(j,i);
    }

    EXPECT_FALSE( diff(matrixComplex, sample.matrix, 1e-12) );
}

TEST_F(CholeskyRealTest, getTwoBodySampleFromAuxForce)
{
    CholeskyReal choleskyReal(dt, choleskyVecs, choleskyBg);
    CholeskyRealAux aux = choleskyReal.sampleAuxFromForce(force);
    CholeskyRealSample sample = choleskyReal.getTwoBodySampleFromAuxForce(aux, force);

    complex<double> w(1.0); complex<double> sqrtMinusDt=sqrt( -dt*complex<double>(1.0,0.0) );
    for(size_t i = 0; i < choleskyNumber; ++i)
    {
        w *= exp( 0.5*force(i)*force(i) -aux(i)*force(i) -aux(i)*sqrtMinusDt*choleskyBg(i) );
    }
    EXPECT_COMPLEX_NEAR( w, exp(sample.logw), 1e-12 );

    TensorHao<double, 2> matrixReal(L,L); matrixReal=0.0;
    for(size_t i = 0; i < choleskyNumber; ++i)
    {
        matrixReal += aux(i) * choleskyVecs[i];
    }
    TensorHao< complex<double>, 2> matrixComplex(L,L);
    for(size_t i = 0; i <L ; ++i)
    {
        for(size_t j = 0; j < L; ++j) matrixComplex(j,i) = sqrtMinusDt * matrixReal(j,i);
    }

    EXPECT_FALSE( diff(matrixComplex, sample.matrix, 1e-12) );
}