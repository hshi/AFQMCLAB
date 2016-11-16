//
// Created by boruoshihao on 10/27/16.
//
#include "../../../libhao/test_hao/gtest_custom.h"
#include "../../interface/include/Lanczos.h"
#include "../../../libhao/math_hao/include/simple_fun.h"
#include "realMaterial.h"

using namespace std;
using namespace tensor_hao;

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
    vector<TwoBody> upup(4),updn(5),dndn(7);

    for(size_t i = 0; i < up.size(); ++i)   up[i]   = { i, i+1, complex<double>(i+2, i+3) };
    for(size_t i = 0; i < dn.size(); ++i)   dn[i]   = { i, i-1, complex<double>(i-2, i-3) };
    for(size_t i = 0; i < upup.size(); ++i) upup[i] = { i, i+1, i+2, i+3, complex<double>(i+4, i+5)  };
    for(size_t i = 0; i < updn.size(); ++i) updn[i] = { i, i+6, i+7, i+8, complex<double>(i+9, i+10) };
    for(size_t i = 0; i < dndn.size(); ++i) dndn[i] = { i, i-6, i-7, i-8, complex<double>(i-9, i-10) };

    RealMaterial H(L, Nup, Ndn);
    H.setUp(up); H.setDn(dn);
    H.setUpUp(upup);
    H.setUpDn(updn);
    H.setDnDn(dndn);

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
        EXPECT_EQ( upup[m].i, HNew.getUpUp()[m].i);
        EXPECT_EQ( upup[m].j, HNew.getUpUp()[m].j);
        EXPECT_EQ( upup[m].k, HNew.getUpUp()[m].k);
        EXPECT_EQ( upup[m].l, HNew.getUpUp()[m].l);
        EXPECT_COMPLEXDOUBLE_EQ( upup[m].V, HNew.getUpUp()[m].V);
    }

    for(size_t m = 0; m < updn.size(); ++m)
    {
        EXPECT_EQ( updn[m].i, HNew.getUpDn()[m].i);
        EXPECT_EQ( updn[m].j, HNew.getUpDn()[m].j);
        EXPECT_EQ( updn[m].k, HNew.getUpDn()[m].k);
        EXPECT_EQ( updn[m].l, HNew.getUpDn()[m].l);
        EXPECT_COMPLEXDOUBLE_EQ( updn[m].V, HNew.getUpDn()[m].V);
    }

    for(size_t m = 0; m < dndn.size(); ++m)
    {
        EXPECT_EQ( dndn[m].i, HNew.getDnDn()[m].i);
        EXPECT_EQ( dndn[m].j, HNew.getDnDn()[m].j);
        EXPECT_EQ( dndn[m].k, HNew.getDnDn()[m].k);
        EXPECT_EQ( dndn[m].l, HNew.getDnDn()[m].l);
        EXPECT_COMPLEXDOUBLE_EQ( dndn[m].V, HNew.getDnDn()[m].V);
    }
}

TEST(realMaterialTest, Lanczos)
{
    size_t L(6), Nup(2),Ndn(3);
    TensorHao<complex<double>, 2> H0Up(L,L); randomFill(H0Up); H0Up += conjtrans(H0Up);
    TensorHao<complex<double>, 2> H0Dn(L,L); randomFill(H0Dn); H0Dn += conjtrans(H0Dn);

    vector<OneBody> up, dn;
    for(size_t i = 0; i < L; ++i)
    {
        for(size_t j = 0; j < L; ++j)
        {
            up.push_back( { j,i, H0Up(j,i) } );
            dn.push_back( { j,i, H0Dn(j,i) } );
        }

    }

    TensorHao<double, 1> Hd(L); double E_exact(0);
    eigen_cpu(H0Up, Hd);  for(size_t k = 0; k < Nup; ++k)  E_exact += Hd(k);
    eigen_cpu(H0Dn, Hd);  for(size_t k = 0; k < Ndn; ++k)  E_exact += Hd(k);

    RealMaterial H(L, Nup, Ndn); H.setUp(up); H.setDn(dn);
    Lanczos lan(H);
    lan.findEigen(1);
    EXPECT_NEAR( E_exact , lan.getEigenvalue(0), 1e-10 );
}