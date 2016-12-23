//
// Created by boruoshihao on 10/27/16.
//
#include "../../../../common/testHao/gtest_custom.h"
#include "../../../interface/include/LanczosInterface.h"
#include "../../../../common/mathHao/include/simple_fun.h"
#include "../include/realMaterial.h"

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
    vector<LanOneBody> up(8), dn(3);
    vector<LanTwoBody> upup(4),updn(5),dndn(7);

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

    remove( filename.c_str() );
}

TEST(realMaterialTest, LanczosOneBody)
{
    size_t L(6), Nup(2),Ndn(3);
    TensorHao<complex<double>, 2> H0Up(L,L); randomFill(H0Up); H0Up += conjtrans(H0Up);
    TensorHao<complex<double>, 2> H0Dn(L,L); randomFill(H0Dn); H0Dn += conjtrans(H0Dn);

    vector<LanOneBody> up, dn;
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

TEST(realMaterialTest, applyCupToWf)
{
    size_t L(6), Nup(2), Ndn(3);
    RealMaterial H(L, Nup, Ndn);

    size_t NHilbert = H.getWfSize();
    LanczosBasisWf wfLeft(NHilbert), wfRight(NHilbert), wfRightTemp, wfLeftTemp;
    randomFill(wfLeft.wfRef());
    randomFill(wfRight.wfRef());

    vector<LanOneOperator> C(1);
    C[0].C = 1.0;
    complex<double> overlapExact, overlap;
    for(size_t i = 0; i < L; ++i)
    {
        for(size_t j = 0; j < L; ++j)
        {
            H.applyCupiDaggerCupjToWf(wfRight, wfRightTemp, i, j);
            overlapExact = wfLeft.calculateOverlapWith(wfRightTemp);

            C[0].i = j;
            H.applyCupToWf(wfRight, wfRightTemp, C);
            C[0].i = i;
            H.applyCupToWf(wfLeft, wfLeftTemp, C);
            overlap = wfLeftTemp.calculateOverlapWith(wfRightTemp);

            EXPECT_COMPLEX_NEAR(overlapExact, overlap, 1e-12 * abs(overlap));
        }
    }
}

TEST(realMaterialTest, applyCdnToWf)
{
    size_t L(6), Nup(2), Ndn(3);
    RealMaterial H(L, Nup, Ndn);

    size_t NHilbert = H.getWfSize();
    LanczosBasisWf wfLeft(NHilbert), wfRight(NHilbert), wfRightTemp, wfLeftTemp;
    randomFill(wfLeft.wfRef());
    randomFill(wfRight.wfRef());

    vector<LanOneOperator> C(1);
    C[0].C = 1.0;
    complex<double> overlapExact, overlap;
    for(size_t i = 0; i < L; ++i)
    {
        for(size_t j = 0; j < L; ++j)
        {
            H.applyCdniDaggerCdnjToWf(wfRight, wfRightTemp, i, j);
            overlapExact = wfLeft.calculateOverlapWith(wfRightTemp);

            C[0].i = j;
            H.applyCdnToWf(wfRight, wfRightTemp, C);
            C[0].i = i;
            H.applyCdnToWf(wfLeft, wfLeftTemp, C);
            overlap = wfLeftTemp.calculateOverlapWith(wfRightTemp);

            EXPECT_COMPLEX_NEAR(overlapExact, overlap, 1e-12 * abs(overlap));
        }
    }
}

TEST(realMaterialTest, applyCDaggerUpToWf)
{
    size_t L(6), Nup(2),Ndn(3);
    RealMaterial H(L, Nup, Ndn);

    size_t NHilbert = H.getWfSize();
    LanczosBasisWf wfLeft(NHilbert), wfRight(NHilbert), wfRightTemp, wfLeftTemp;
    randomFill( wfLeft.wfRef() ); randomFill( wfRight.wfRef() );


    vector<LanOneOperator> C(1); C[0].C = 1.0;
    complex<double> overlapExact, overlap;
    for(size_t i = 0; i < L; ++i)
    {
        for(size_t j = i+1; j < L; ++j)
        {
            H.applyCupiDaggerCupjToWf(wfRight, wfRightTemp, i, j);
            overlapExact =  - wfLeft.calculateOverlapWith(wfRightTemp);

            C[0].i = i; H.applyCupDaggerToWf(wfRight, wfRightTemp, C);
            C[0].i = j; H.applyCupDaggerToWf(wfLeft, wfLeftTemp, C);
            overlap = wfLeftTemp.calculateOverlapWith(wfRightTemp);

            EXPECT_COMPLEX_NEAR( overlapExact, overlap, 1e-12 * abs(overlap) );
        }
    }
}

TEST(realMaterialTest, applyCDaggerDnToWf)
{
    size_t L(6), Nup(2),Ndn(3);
    RealMaterial H(L, Nup, Ndn);

    size_t NHilbert = H.getWfSize();
    LanczosBasisWf wfLeft(NHilbert), wfRight(NHilbert), wfRightTemp, wfLeftTemp;
    randomFill( wfLeft.wfRef() ); randomFill( wfRight.wfRef() );


    vector<LanOneOperator> C(1); C[0].C = 1.0;
    complex<double> overlapExact, overlap;
    for(size_t i = 0; i < L; ++i)
    {
        for(size_t j = i+1; j < L; ++j)
        {
            H.applyCdniDaggerCdnjToWf(wfRight, wfRightTemp, i, j);
            overlapExact =  - wfLeft.calculateOverlapWith(wfRightTemp);

            C[0].i = i; H.applyCdnDaggerToWf(wfRight, wfRightTemp, C);
            C[0].i = j; H.applyCdnDaggerToWf(wfLeft, wfLeftTemp, C);
            overlap = wfLeftTemp.calculateOverlapWith(wfRightTemp);

            EXPECT_COMPLEX_NEAR( overlapExact, overlap, 1e-12 * abs(overlap) );
        }
    }
}

class realMaterialHubbardTest: public ::testing::Test
{
 public:
    size_t L=4, Nup=2, Ndn=3;
    vector<LanOneBody> up, dn;
    vector<LanTwoBody> upDn;

    realMaterialHubbardTest( )
    {
        up.push_back( {0, 3, {-0.309016994374947, 0.951056516295154} } );
        up.push_back( {0, 1, {-0.309016994374947,-0.951056516295154} } );
        up.push_back( {1, 2, {-0.309016994374947,-0.951056516295154} } );
        up.push_back( {1, 0, {-0.309016994374947, 0.951056516295154} } );
        up.push_back( {2, 3, {-0.309016994374947,-0.951056516295154} } );
        up.push_back( {2, 1, {-0.309016994374947, 0.951056516295154} } );
        up.push_back( {3, 0, {-0.309016994374947,-0.951056516295154} } );
        up.push_back( {3, 2, {-0.309016994374947, 0.951056516295154} } );
        dn = up;
        upDn.push_back( {0,0,0,0,4} );
        upDn.push_back( {1,1,1,1,4} );
        upDn.push_back( {2,2,2,2,4} );
        upDn.push_back( {3,3,3,3,4} );
    }

    ~realMaterialHubbardTest( )
    {
    }
};

TEST_F(realMaterialHubbardTest, energy)
{
    RealMaterial H(L, Nup, Ndn); H.setUp(up); H.setDn(dn); H.setUpDn(upDn);
    Lanczos lan(H);
    lan.findEigen(1);
    double E_exact = 0.877119735524673;
    EXPECT_NEAR( E_exact , lan.getEigenvalue(0), 1e-10 );

    const LanczosBasisWf & wf0 = lan.getEigenstate(0);
    LanczosBasisWf wfPrime = lan.getLanWavefunction(0);

    H.applyKToWf(wf0, wfPrime);
    complex<double> K = wf0.calculateOverlapWith(wfPrime);
    complex<double> K_Exact(-3.87084415356266, 0);
    EXPECT_COMPLEX_NEAR( K_Exact , K, 1e-10 );

    H.applyVToWf(wf0, wfPrime);
    complex<double> V = wf0.calculateOverlapWith(wfPrime);
    complex<double> V_Exact(4.74796388908733, 0);
    EXPECT_COMPLEX_NEAR( V_Exact , V, 1e-10 );
}

TEST_F(realMaterialHubbardTest, spinCorrelation)
{
    RealMaterial H(L, Nup, Ndn); H.setUp(up); H.setDn(dn); H.setUpDn(upDn);
    Lanczos lan(H);
    lan.findEigen(1);

    const LanczosBasisWf & wf0 = lan.getEigenstate(0);
    LanczosBasisWf wfPrime = lan.getLanWavefunction(0);

    H.applySiSjToWf(wf0, wfPrime, 0, 0);
    complex<double> S0S0 = wf0.calculateOverlapWith(wfPrime);
    complex<double> S0S0_Exact(0.49237839, 0);
    EXPECT_COMPLEX_NEAR( S0S0 , S0S0_Exact, 1e-8 );

    H.applySiSjToWf(wf0, wfPrime, 0, 1);
    complex<double> S0S1 = wf0.calculateOverlapWith(wfPrime);
    complex<double> S0S1_Exact(-0.13413708, 0);
    EXPECT_COMPLEX_NEAR( S0S1 , S0S1_Exact, 1e-8 );
}

TEST_F(realMaterialHubbardTest, spinZCorrelation)
{
    RealMaterial H(L, Nup, Ndn); H.setUp(up); H.setDn(dn); H.setUpDn(upDn);
    Lanczos lan(H);
    lan.findEigen(1);

    const LanczosBasisWf & wf0 = lan.getEigenstate(0);
    LanczosBasisWf wfPrime = lan.getLanWavefunction(0);

    H.applySziSzjToWf(wf0, wfPrime, 0, 0);
    complex<double> Sz0Sz0 = wf0.calculateOverlapWith(wfPrime);
    complex<double> Sz0Sz0_Exact(0.16412613, 0);
    EXPECT_COMPLEX_NEAR( Sz0Sz0 , Sz0Sz0_Exact, 1e-8 );

    H.applySziSzjToWf(wf0, wfPrime, 0, 1);
    complex<double> Sz0Sz1 = wf0.calculateOverlapWith(wfPrime);
    complex<double> Sz0Sz1_Exact(-0.04471236, 0);
    EXPECT_COMPLEX_NEAR( Sz0Sz1 , Sz0Sz1_Exact, 1e-8 );
}

TEST_F(realMaterialHubbardTest, SplusSminusCorrelation)
{
    RealMaterial H(L, Nup, Ndn); H.setUp(up); H.setDn(dn); H.setUpDn(upDn);
    Lanczos lan(H);
    lan.findEigen(1);

    const LanczosBasisWf & wf0 = lan.getEigenstate(0);
    LanczosBasisWf wfPrime = lan.getLanWavefunction(0);

    H.applySplusiSminusjToWf(wf0, wfPrime, 0, 0);
    complex<double> Sp0Sm0 = wf0.calculateOverlapWith(wfPrime);
    complex<double> Sp0Sm0_Exact(0.2032522570, 0);
    EXPECT_COMPLEX_NEAR( Sp0Sm0 , Sp0Sm0_Exact, 1e-8 );


    H.applySplusiSminusjToWf(wf0, wfPrime, 0, 1);
    complex<double> Sp0Sm1 = wf0.calculateOverlapWith(wfPrime);
    double Sp0Sm1Real_Exact(-0.08942472);
    EXPECT_NEAR( Sp0Sm1.real() , Sp0Sm1Real_Exact, 1e-8 );
}

TEST_F(realMaterialHubbardTest, NNCorrelation)
{
    RealMaterial H(L, Nup, Ndn); H.setUp(up); H.setDn(dn); H.setUpDn(upDn);
    Lanczos lan(H);
    lan.findEigen(1);

    const LanczosBasisWf & wf0 = lan.getEigenstate(0);
    LanczosBasisWf wfPrime = lan.getLanWavefunction(0);

    H.applyNiNjToWf(wf0, wfPrime, 0, 0);
    complex<double> N0N0 = wf0.calculateOverlapWith(wfPrime);
    complex<double> N0N0_Exact(1.8434954861, 0);
    EXPECT_COMPLEX_NEAR( N0N0 , N0N0_Exact, 1e-8 );

    H.applyNiNjToWf(wf0, wfPrime, 0, 1);
    complex<double> N0N1 = wf0.calculateOverlapWith(wfPrime);
    complex<double> N0N1_Exact(0, 0);
    LanczosBasisWf wfPrimePrime = lan.getLanWavefunction(1);

    H.applyCupiDaggerCupjToWf(wf0, wfPrimePrime, 1, 1);
    H.applyCupiDaggerCupjToWf(wfPrimePrime, wfPrime, 0, 0);
    N0N1_Exact += wf0.calculateOverlapWith(wfPrime);

    H.applyCdniDaggerCdnjToWf(wf0, wfPrimePrime, 1, 1);
    H.applyCdniDaggerCdnjToWf(wfPrimePrime, wfPrime, 0, 0);
    N0N1_Exact += wf0.calculateOverlapWith(wfPrime);

    H.applyCdniDaggerCdnjToWf(wf0, wfPrimePrime, 1, 1);
    H.applyCupiDaggerCupjToWf(wfPrimePrime, wfPrime, 0, 0);
    N0N1_Exact += wf0.calculateOverlapWith(wfPrime);

    H.applyCdniDaggerCdnjToWf(wf0, wfPrimePrime, 0, 0);
    H.applyCupiDaggerCupjToWf(wfPrimePrime, wfPrime, 1, 1);
    N0N1_Exact += wf0.calculateOverlapWith(wfPrime);

    EXPECT_COMPLEX_NEAR( N0N1 , N0N1_Exact, 1e-8 );
}

TEST_F(realMaterialHubbardTest, DDCorrelation)
{
    RealMaterial H(L, Nup, Ndn); H.setUp(up); H.setDn(dn); H.setUpDn(upDn);
    Lanczos lan(H);
    lan.findEigen(1);

    const LanczosBasisWf & wf0 = lan.getEigenstate(0);
    LanczosBasisWf wfPrime = lan.getLanWavefunction(0);

    H.applyDiDaggerDjToWf(wf0, wfPrime, 0, 0);
    complex<double> D0D0 = wf0.calculateOverlapWith(wfPrime);
    complex<double> D0D0_exact(0.2967477430, 0);
    EXPECT_COMPLEX_NEAR( D0D0 , D0D0_exact, 1e-8 );

    H.applyDiDaggerDjToWf(wf0, wfPrime, 0, 1);
    complex<double> D0D1 = wf0.calculateOverlapWith(wfPrime);
    double D0D1Real_exact(-0.0231103600);
    EXPECT_NEAR( D0D1.real(), D0D1Real_exact, 1e-8 );
}

TEST_F(realMaterialHubbardTest, GreenFunction)
{
    RealMaterial H(L, Nup, Ndn); H.setUp(up); H.setDn(dn); H.setUpDn(upDn);
    Lanczos lan(H);
    lan.findEigen(1);

    const LanczosBasisWf & wf0 = lan.getEigenstate(0);
    LanczosBasisWf wfPrime = lan.getLanWavefunction(0);

    H.applyCupiDaggerCupjToWf(wf0, wfPrime, 0, 1);
    complex<double> Cup0Cup1 = wf0.calculateOverlapWith(wfPrime);
    complex<double> Cup0Cup1_exact(0.215766341130938, -0.225593142085703);
    EXPECT_COMPLEX_NEAR( Cup0Cup1 , Cup0Cup1_exact, 1e-8 );

    H.applyCdniDaggerCdnjToWf(wf0, wfPrime, 0, 1);
    complex<double> Cdn0Cdn1 = wf0.calculateOverlapWith(wfPrime);
    complex<double> Cdn0Cdn1_exact(0.007097970056088223, -0.210749654045575);
    EXPECT_COMPLEX_NEAR( Cdn0Cdn1 , Cdn0Cdn1_exact, 1e-8 );
}