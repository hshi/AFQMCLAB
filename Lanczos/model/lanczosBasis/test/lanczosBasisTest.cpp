//
// Created by boruoshihao on 10/28/16.
//
#include "../include/lanczosBasis.h"
#include "../../../../libhao/testHao/gtest_custom.h"
#include "../../../../libhao/mathHao/include/simple_fun.h"

using namespace std;
using namespace tensor_hao;

TEST(LanczosBasis, binomial)
{
    size_t L(10), N(5);
    LanczosBasis lanBasis(L, N);
    auto &binomialTable = lanBasis.getBinomialTable();
    for(size_t i = 0; i < L; ++i)
    {
        for(size_t j = 0; j < N; ++j)
        {
            if( j > i ) EXPECT_EQ( static_cast<size_t>(0), binomialTable(i,j) );
            else EXPECT_EQ( binomialCoeff(i,j), binomialTable(i,j) );
        }
    }
}

TEST(LanczosBasis, nextAndGetIndexFromPosition)
{
    size_t L(10), N(5);
    LanczosBasis lanBasis(L, N);
    auto &binomialTable = lanBasis.getBinomialTable();
    auto &pp = lanBasis.getPositionOfParticle();

    size_t NHilbert = binomialTable(L, N);
    for(size_t i = 0; i < NHilbert; ++i)
    {
        EXPECT_EQ( i, lanBasis.getIndex() );
        EXPECT_EQ( i, lanBasis.getIndexFromPosition(pp) );
        if( i != (NHilbert-1) ) EXPECT_EQ( 0, lanBasis.next() );
        else EXPECT_EQ( 1, lanBasis.next() );
    }
}

TEST(LanczosBasis, reSet)
{
    size_t L(10), N(5);
    LanczosBasis lanBasis(L, N), lanBasisExact(L,N);
    auto &binomialTable = lanBasis.getBinomialTable();
    auto &pp = lanBasis.getPositionOfParticle();
    auto &epp = lanBasis.getEmptyPositionForParticle();

    size_t NHilbert = binomialTable(L, N);
    for(size_t i = 0; i < NHilbert; ++i)
    {
        lanBasis.reSet(i);

        EXPECT_EQ( i, lanBasis.getIndex() );
        EXPECT_FALSE( diff( lanBasisExact.getPositionOfParticle(), pp, 1e-12) );
        EXPECT_FALSE( diff( lanBasisExact.getEmptyPositionForParticle(), epp, 1e-12) );

        lanBasisExact.next();
    }
}

TEST(LanczosBasis, getInfoByC2DaggerC2)
{
    size_t L(5), N(3);
    LanczosBasis lanBasis(L, N);

    size_t indexExact[10] = {0,1,2,3,4,5,6,7,8,9};
    int coeExact[10]={1,0,1,1,0,1,1,0,0,1};
    TableElement info;
    auto &binomialTable = lanBasis.getBinomialTable();
    size_t NHilbert = binomialTable(L, N);
    for(size_t i = 0; i < NHilbert; ++i)
    {
        info = lanBasis.getInfoByCiDaggerCj(2, 2);
        EXPECT_EQ(indexExact[i], info.index);
        EXPECT_EQ(coeExact[i], info.coefficient);
        lanBasis.next();
    }
}

TEST(LanczosBasis, getInfoByC4DaggerC4)
{
    size_t L(5), N(3);
    LanczosBasis lanBasis(L, N);

    size_t indexExact[10] = {0,1,2,3,4,5,6,7,8,9};
    int coeExact[10]={0,0,0,0,1,1,1,1,1,1};
    TableElement info;
    auto &binomialTable = lanBasis.getBinomialTable();
    size_t NHilbert = binomialTable(L, N);
    for(size_t i = 0; i < NHilbert; ++i)
    {
        info = lanBasis.getInfoByCiDaggerCj(4, 4);
        EXPECT_EQ(indexExact[i], info.index);
        EXPECT_EQ(coeExact[i], info.coefficient);
        lanBasis.next();
    }
}

TEST(LanczosBasis, getInfoByC1DaggerC3)
{
    size_t L(5), N(3);
    LanczosBasis lanBasis(L, N);

    size_t indexExact[10] = {0,1,0,3,4,5,6,4,8,6};
    int coeExact[10] ={0,0,-1,0,0,0,0,1,0,-1};
    TableElement info;
    auto &binomialTable = lanBasis.getBinomialTable();
    size_t NHilbert = binomialTable(L, N);
    for(size_t i = 0; i < NHilbert; ++i)
    {
        info = lanBasis.getInfoByCiDaggerCj(1, 3);
        EXPECT_EQ(indexExact[i], info.index);
        EXPECT_EQ(coeExact[i], info.coefficient);
        lanBasis.next();
    }
}

TEST(LanczosBasis, getInfoByC3DaggerC0)
{
    size_t L(5), N(3);
    LanczosBasis lanBasis(L, N);

    size_t indexExact[10] = {3,1,2,3,8,9,6,7,8,9};
    int coeExact[10] ={1,0,0,0,-1,-1,0,0,0,0};
    TableElement info;
    auto &binomialTable = lanBasis.getBinomialTable();
    size_t NHilbert = binomialTable(L, N);
    for(size_t i = 0; i < NHilbert; ++i)
    {
        info = lanBasis.getInfoByCiDaggerCj(3, 0);
        EXPECT_EQ(indexExact[i], info.index);
        EXPECT_EQ(coeExact[i], info.coefficient);
        lanBasis.next();
    }
}

TEST(LanczosBasis, diagonalizeOneBodyMatrix)
{
    size_t L(10), N(5);
    TensorHao<complex<double>, 2> H0(L,L); randomFill(H0); H0 += conjtrans(H0);

    TensorHao<complex<double>, 2> Hv(H0);
    TensorHao<double ,1> He(L);
    eigen_cpu(Hv, He);
    double energyExact(0); for(size_t i = 0; i < N; ++i) energyExact += He(i);

    LanczosBasis lanBasis(L,N);
    auto &binomialTable = lanBasis.getBinomialTable();
    size_t NHilbert = binomialTable(L, N);
    TableElement element;
    TensorHao<complex<double>, 2> HvManyBody(NHilbert, NHilbert);
    HvManyBody = complex<double>(0,0);
    for(size_t k = 0; k < NHilbert; ++k)
    {
        for(size_t i = 0; i < L; ++i)
        {
            for(size_t j = 0; j < L; ++j)
            {
                element = lanBasis.getInfoByCiDaggerCj(i,j);
                HvManyBody( element.index, k ) += element.coefficient * 1.0 * H0(i,j);
            }
        }
        lanBasis.next();
    }
    TensorHao<double, 1> HeManyBody(NHilbert);
    eigen_cpu(HvManyBody, HeManyBody);

    EXPECT_DOUBLE_EQ( energyExact, HeManyBody(0) );
}