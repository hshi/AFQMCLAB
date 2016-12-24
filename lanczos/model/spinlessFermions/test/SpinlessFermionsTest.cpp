//
// Created by boruoshihao on 11/18/16.
//

#include "../../../../common/testHao/gtest_custom.h"
#include "../../../interface/include/LanczosInterface.h"
#include "../../../../common/mathHao/include/simple_fun.h"
#include "../include/SpinlessFermions.h"

using namespace std;
using namespace tensor_hao;

TEST(SpinlessFermionsTest, readWrite)
{
    size_t L(10), N(5);
    vector<LanOneBody> K(8);
    vector<LanTwoBody> V(4);

    for(size_t i = 0; i < K.size(); ++i) K[i] = { i, i+1, complex<double>(i+2, i+3) };
    for(size_t i = 0; i < V.size(); ++i) V[i] = { i, i+1, i+2, i+3, complex<double>(i+4, i+5)  };

    SpinlessFermions H(L, N);
    H.setK(K); H.setV(V);

    string filename = "SpinlessFermions.dat";
    H.write(filename);

    SpinlessFermions HNew(filename);
    EXPECT_EQ( L, HNew.getL()   );
    EXPECT_EQ( N, HNew.getN() );
    EXPECT_EQ( binomialCoeff(L,N), HNew.getWfSize() );

    for(size_t m = 0; m < K.size(); ++m)
    {
        EXPECT_EQ( K[m].i, HNew.getK()[m].i);
        EXPECT_EQ( K[m].j, HNew.getK()[m].j);
        EXPECT_COMPLEXDOUBLE_EQ( K[m].K, HNew.getK()[m].K);
    }

    for(size_t m = 0; m < V.size(); ++m)
    {
        EXPECT_EQ( V[m].i, HNew.getV()[m].i);
        EXPECT_EQ( V[m].j, HNew.getV()[m].j);
        EXPECT_EQ( V[m].k, HNew.getV()[m].k);
        EXPECT_EQ( V[m].l, HNew.getV()[m].l);
        EXPECT_COMPLEXDOUBLE_EQ( V[m].V, HNew.getV()[m].V);
    }

    remove( filename.c_str() );
}

TEST(SpinlessFermionsTest, LanczosOneBody)
{
    size_t L(10), N(5);
    TensorHao<complex<double>, 2> H0(L,L); randomFill(H0); H0 += conjtrans(H0);

    TensorHao<complex<double>, 2> Hv(H0);
    TensorHao<double ,1> He(L);
    eigen_cpu(Hv, He);
    double energyExact = He.sum(0, N, 1);

    vector<LanOneBody> K;
    for(size_t i = 0; i < L; ++i)
    {
        for(size_t j = 0; j < L; ++j)
        {
            K.push_back( {j,i, H0(j,i) } );
        }
    }
    SpinlessFermions HSpinless(L, N); HSpinless.setK(K);

    Lanczos lan(HSpinless);
    lan.findEigen(1);
    EXPECT_NEAR( energyExact , lan.getEigenvalue(0), 1e-10 );
}

TEST(SpinlessFermionsTest, applyCreationOperatorsToWf)
{
    size_t L(10), N(3);
    size_t NHilbert = binomialCoeff(L, N);
    SpinlessFermions HSpinless(L, N);

    LanczosBasisWf wfLeft(NHilbert), wfRight(NHilbert), wfRightTemp, wfLeftTemp;
    randomFill( wfLeft.wfRef() ); randomFill( wfRight.wfRef() );

    vector<LanOneOperator> C(1); C[0].C = 1.0;
    complex<double> overlapExact, overlap;
    for(size_t i = 0; i < L; ++i)
    {
        for(size_t j = i+1; j < L; ++j)
        {
            HSpinless.applyCiDaggerCjToWf(wfRight, wfRightTemp, i, j);
            overlapExact = - wfLeft.calculateOverlapWith(wfRightTemp);

            C[0].i = i; HSpinless.applyCreationOperatorsToWf(wfRight, wfRightTemp, C);
            C[0].i = j; HSpinless.applyCreationOperatorsToWf(wfLeft, wfLeftTemp, C);
            overlap = wfLeftTemp.calculateOverlapWith(wfRightTemp);
            EXPECT_COMPLEX_NEAR( overlapExact, overlap, 1e-12 * abs(overlap) );
        }
    }
}

TEST(SpinlessFermionsTest, applyAnnihilationOperatorsToWf)
{
    size_t L(10), N(5);
    size_t NHilbert = binomialCoeff(L, N);
    SpinlessFermions HSpinless(L, N);

    LanczosBasisWf wfLeft(NHilbert), wfRight(NHilbert), wfRightTemp, wfLeftTemp;
    randomFill( wfLeft.wfRef() ); randomFill( wfRight.wfRef() );

    vector<LanOneOperator> C(1); C[0].C = 1.0;
    complex<double> overlapExact, overlap;
    for(size_t i = 0; i < L; ++i)
    {
        for(size_t j = 0; j < L; ++j)
        {
            HSpinless.applyCiDaggerCjToWf(wfRight, wfRightTemp, i, j);
            overlapExact = wfLeft.calculateOverlapWith(wfRightTemp);

            C[0].i = j; HSpinless.applyAnnihilationOperatorsToWf(wfRight, wfRightTemp, C);
            C[0].i = i; HSpinless.applyAnnihilationOperatorsToWf(wfLeft, wfLeftTemp, C);
            overlap = wfLeftTemp.calculateOverlapWith(wfRightTemp);

            EXPECT_COMPLEX_NEAR( overlapExact, overlap, 1e-12 * abs(overlap) );
        }
    }
}