//
// Created by boruoshihao on 10/28/16.
//
#include "../include/lanczosBasis.h"
#include "../../../../libhao/testHao/gtest_custom.h"
#include "../../../../libhao/mathHao/include/simple_fun.h"
#include "../../../../libhao/tensorHao/include/tensor_all.h"

using namespace std;
using namespace tensor_hao;

TEST(LanczosBasis, binomial)
{
    size_t L(10), N(5);
    LanczosBasis lanBasis(L, N);
    for(size_t i = 0; i < L; ++i)
    {
        for(size_t j = 0; j < N; ++j)
        {
            if( j > i ) EXPECT_EQ( static_cast<size_t>(0), lanBasis.binomial(i,j) );
            else EXPECT_EQ( binomialCoeff(i,j), lanBasis.binomial(i,j) );
        }
    }
}

TEST(LanczosBasis, stack)
{
    size_t L(10), N(5);
    LanczosBasis lanBasis(L, N);
    size_t NHilbert = lanBasis.binomial(L, N);

    const size_t *pp = lanBasis.getPositionOfParticle();

    for(size_t i = 0; i < NHilbert; ++i)
    {
        EXPECT_EQ( i, lanBasis.getIndexFromPosition(pp) );
        if( i != (NHilbert-1) ) EXPECT_EQ( 0, lanBasis.next() );
        else EXPECT_EQ( 1, lanBasis.next() );
    }

//    for(size_t j = 0; j < 100; ++j)
//    {
//        lanBasis.next();
//        cout<<lanBasis.getIndexFromPosition( pp )<<" ! ";
//        for(size_t i = 0; i < N; ++i) cout<<pp[i]<<" ";
//        cout<<endl;
//    }

}

TEST(LanczosBasis, heap)
{
    size_t L(35), N(33);
    LanczosBasis lanBasis(L, N);
    size_t NHilbert = lanBasis.binomial(L, N);

    const size_t *pp = lanBasis.getPositionOfParticle();

    for(size_t i = 0; i < NHilbert; ++i)
    {
        EXPECT_EQ( i, lanBasis.getIndexFromPosition(pp) );
        if( i != (NHilbert-1) ) EXPECT_EQ( 0, lanBasis.next() );
        else EXPECT_EQ( 1, lanBasis.next() );
    }
}

TEST(LanczosBasis, getInfoByC2DaggerC2)
{
    size_t L(5), N(3);
    LanczosBasis lanBasis(L, N);

    size_t indexExact[10] = {0,1,2,3,4,5,6,7,8,9};
    int coeExact[10]={1,0,1,1,0,1,1,0,0,1};
    TableElement info;
    size_t NHilbert = lanBasis.binomial(L, N);
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
    size_t NHilbert = lanBasis.binomial(L, N);
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
    size_t NHilbert = lanBasis.binomial(L, N);
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
    size_t NHilbert = lanBasis.binomial(L, N);
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
    size_t NHilbert = lanBasis.binomial(L, N);
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
