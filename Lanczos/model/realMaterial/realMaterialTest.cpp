//
// Created by boruoshihao on 10/27/16.
//
#include "../../../libhao/test_hao/gtest_custom.h"
#include "../../interface/include/Lanczos.h"
#include "../../../libhao/math_hao/include/simple_fun.h"
#include "realMaterial.h"

using namespace std;

TEST(realMaterialTest, voidConstruction)
{
    RealMaterial H;
    EXPECT_EQ( 0, H.getL()   );
    EXPECT_EQ( 0, H.getNup() );
    EXPECT_EQ( 0, H.getNdn() );
    EXPECT_EQ( 1, H.getWfSize() );
    EXPECT_EQ( 1, H.getNHilbertUp() );
    EXPECT_EQ( 1, H.getNHilbertDn() );
}

TEST(realMaterialTest, LNupNdnConstruction)
{
    size_t L(10), Nup(5), Ndn(6);
    RealMaterial H(L, Nup, Ndn);
    EXPECT_EQ( L,   H.getL()   );
    EXPECT_EQ( Nup, H.getNup() );
    EXPECT_EQ( Ndn, H.getNdn() );
    EXPECT_EQ( binomialCoeff(L,Nup) * binomialCoeff(L,Ndn), H.getWfSize() );
    EXPECT_EQ( binomialCoeff(L,Nup), H.getNHilbertUp() );
    EXPECT_EQ( binomialCoeff(L,Ndn), H.getNHilbertDn() );
}

TEST(realMaterialTest, readWrite)
{
    size_t L(10), Nup(5), Ndn(6);
    vector<OneBody> up(8), dn(3);
    vector<TwoBody> upup(4),updn(5),dnup(6),dndn(7);

    for(size_t i = 0; i < up.size(); ++i)   up[i]   = { i, i+1, complex<double>(i+2, i+3) };
    for(size_t i = 0; i < dn.size(); ++i)   dn[i]   = { i, i-1, complex<double>(i-2, i-3) };
    for(size_t i = 0; i < upup.size(); ++i) upup[i] = { i, i+1, i+2, i+3, complex<double>(i+4, i+5)  };
    for(size_t i = 0; i < updn.size(); ++i) updn[i] = { i, i+6, i+7, i+8, complex<double>(i+9, i+10) };
    for(size_t i = 0; i < dnup.size(); ++i) dnup[i] = { i, i-1, i-7, i-8, complex<double>(i-4, i-5)  };
    for(size_t i = 0; i < dndn.size(); ++i) dndn[i] = { i, i-6, i-7, i-8, complex<double>(i-9, i-10) };

    RealMaterial H(L, Nup, Ndn);
    H.setUp(up); H.setDn(dn); H.setUpup(upup); H.setUpdn(updn); H.setDnup(dnup); H.setDndn(dndn);

    string filename = "realMaterial.dat";
    H.write(filename);

    RealMaterial HNew(filename);
    EXPECT_EQ( L,   HNew.getL()   );
    EXPECT_EQ( Nup, HNew.getNup() );
    EXPECT_EQ( Ndn, HNew.getNdn() );
    EXPECT_EQ( binomialCoeff(L,Nup) * binomialCoeff(L,Ndn), HNew.getWfSize() );
    EXPECT_EQ( binomialCoeff(L,Nup), HNew.getNHilbertUp() );
    EXPECT_EQ( binomialCoeff(L,Ndn), HNew.getNHilbertDn() );

    for(size_t m = 0; m < up.size(); ++m)
    {
        EXPECT_EQ( up[m].i, HNew.getUp()[m].i);
        EXPECT_EQ( up[m].j, HNew.getUp()[m].j);
        EXPECT_COMPLEXDOUBLE_EQ( up[m].K, HNew.getUp()[m].K);
    }

    for(size_t m = 0; m < dn.size(); ++m)
    {
        EXPECT_EQ( dn[m].i, HNew.getDn()[m].i);
        EXPECT_EQ( dn[m].j, HNew.getDn()[m].j);
        EXPECT_COMPLEXDOUBLE_EQ( dn[m].K, HNew.getDn()[m].K);
    }

    for(size_t m = 0; m < upup.size(); ++m)
    {
        EXPECT_EQ( upup[m].i, HNew.getUpup()[m].i);
        EXPECT_EQ( upup[m].j, HNew.getUpup()[m].j);
        EXPECT_EQ( upup[m].k, HNew.getUpup()[m].k);
        EXPECT_EQ( upup[m].l, HNew.getUpup()[m].l);
        EXPECT_COMPLEXDOUBLE_EQ( upup[m].V, HNew.getUpup()[m].V);
    }

    for(size_t m = 0; m < updn.size(); ++m)
    {
        EXPECT_EQ( updn[m].i, HNew.getUpdn()[m].i);
        EXPECT_EQ( updn[m].j, HNew.getUpdn()[m].j);
        EXPECT_EQ( updn[m].k, HNew.getUpdn()[m].k);
        EXPECT_EQ( updn[m].l, HNew.getUpdn()[m].l);
        EXPECT_COMPLEXDOUBLE_EQ( updn[m].V, HNew.getUpdn()[m].V);
    }

    for(size_t m = 0; m < dnup.size(); ++m)
    {
        EXPECT_EQ( dnup[m].i, HNew.getDnup()[m].i);
        EXPECT_EQ( dnup[m].j, HNew.getDnup()[m].j);
        EXPECT_EQ( dnup[m].k, HNew.getDnup()[m].k);
        EXPECT_EQ( dnup[m].l, HNew.getDnup()[m].l);
        EXPECT_COMPLEXDOUBLE_EQ( dnup[m].V, HNew.getDnup()[m].V);
    }

    for(size_t m = 0; m < dndn.size(); ++m)
    {
        EXPECT_EQ( dndn[m].i, HNew.getDndn()[m].i);
        EXPECT_EQ( dndn[m].j, HNew.getDndn()[m].j);
        EXPECT_EQ( dndn[m].k, HNew.getDndn()[m].k);
        EXPECT_EQ( dndn[m].l, HNew.getDndn()[m].l);
        EXPECT_COMPLEXDOUBLE_EQ( dndn[m].V, HNew.getDndn()[m].V);
    }
}