//
// Created by boruoshihao on 10/28/16.
//
#include "lanczosBasis.h"
#include "../../../libhao/test_hao/gtest_custom.h"
#include "../../../libhao/math_hao/include/simple_fun.h"

using namespace std;

TEST(LanczosBasis, stack)
{
    size_t L(10), N(5);
    size_t NHilbert = binomialCoeff(L, N);
    LanczosBasis lanBasis(L, N);

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
    size_t NHilbert = binomialCoeff(L, N);
    LanczosBasis lanBasis(L, N);

    const size_t *pp = lanBasis.getPositionOfParticle();

    for(size_t i = 0; i < NHilbert; ++i)
    {
        EXPECT_EQ( i, lanBasis.getIndexFromPosition(pp) );
        if( i != (NHilbert-1) ) EXPECT_EQ( 0, lanBasis.next() );
        else EXPECT_EQ( 1, lanBasis.next() );
    }
}