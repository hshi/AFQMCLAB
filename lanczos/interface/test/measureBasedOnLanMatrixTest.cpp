#include "../../../common/testHao/gtest_custom.h"
#include "../include/measureBasedOnLanMatrix.h"
#include "Hmatrix.h"

using namespace std;
using namespace tensor_hao;

TEST(measureBasedOnLanMatrixTest, returnLogExpMinusTauModel)
{
    //Set parameters
    size_t L = 10;
    Hmatrix hmatrix; hmatrix.resize(L);
    LanczosBasisWf wf(L); wf.randomFill();
    TensorHao<double,1> tau(3); tau= {0, 1, 2 };

    //Diagonalize hmatrix
    TensorHao<complex<double>,2> hv = hmatrix.getHm();
    TensorHao<double,1> he(L);
    eigen_cpu( hv, he);
    TensorHao<complex<double>,1> he_cd(L);
    for(size_t i = 0; i < L; ++i) he_cd(i) = he(i);

    //Get exact solution
    auto & vec = wf.getWf();
    TensorHao<complex<double>, 1> vecNewBase(L), vecNewExp(L);
    for(size_t i = 0; i < L; ++i)
    {
        vecNewBase(i) = 0.0;
        for(size_t j = 0; j < L; ++j) vecNewBase(i) +=  conj( hv(j, i) ) * vec(j);
    }
    TensorHao<double,1> expMTauH_Exact( tau.size() );
    for(size_t i = 0; i < tau.size(); ++i)
    {
        vecNewExp = exp( -complex<double>(tau(i),0) * he_cd) * vecNewBase;
        expMTauH_Exact(i) = ( ( conj( vecNewBase ) * vecNewExp ).sum() ).real();
    }

    //To be tested
    MeasureBasedOnLanMatrix meas(hmatrix, wf);
    TensorHao<double,1> expMTauH = tensor_hao::exp( meas.returnLogExpMinusTauModel(tau, L) );

    for(size_t i = 0; i < tau.size(); ++i)
    {
        EXPECT_NEAR( expMTauH(i) , expMTauH_Exact(i), 1e-12*abs(expMTauH_Exact(i)) );
    }
}

TEST(measureBasedOnLanMatrixTest, returnGreenFunction)
{
    //Set parameters
    size_t L = 10;
    Hmatrix hmatrix; hmatrix.resize(L);
    LanczosBasisWf wf(L); wf.randomFill();
    TensorHao<complex<double>,1> omega(3); omega = { {0,1}, {1,2}, {2,3} };

    //To be tested
    MeasureBasedOnLanMatrix meas(hmatrix, wf);
    TensorHao<complex<double>,1> greenFunction = meas.returnGreenFunction(omega, L);

    //Get exact solution
    auto lanabTuple = meas.getLanElements();
    const vector<double> &lana = get<0>(lanabTuple);
    const vector<double> &lanb = get<1>(lanabTuple);
    TensorHao<complex<double>,1> greenFunction_Exact( omega.size() );
    for(size_t i = 0; i < omega.size(); ++i)
    {
        TensorHao<complex<double>,2> hm(L,L); hm = complex<double>(0,0);
        for(size_t j = 0; j < L; ++j) { hm(j, j) = omega(i) - lana[j]; }
        for(size_t j = 1; j < L; ++j) { hm(j, j-1) = -lanb[j]; hm(j-1, j) = -lanb[j]; }
        hm = inverse_cpu( LUconstruct_cpu( hm ) );
        greenFunction_Exact(i) = hm(0,0) * meas.getWfNorm() * meas.getWfNorm();
    }

    for(size_t i = 0; i < omega.size(); ++i)
    {
        EXPECT_COMPLEX_NEAR( greenFunction(i) , greenFunction_Exact(i), 1e-12* abs(greenFunction(i)) );
    }
}

TEST(measureBasedOnLanMatrixTest, readWrite)
{
    //Set parameters
    size_t L = 10;
    Hmatrix hmatrix; hmatrix.resize(L);
    LanczosBasisWf wf(L); wf.randomFill();
    TensorHao<double,1> tau(3); tau= {0, 1, 2 };

    MeasureBasedOnLanMatrix meas(hmatrix, wf);
    TensorHao<double,1> expMTauH = tensor_hao::exp( meas.returnLogExpMinusTauModel(tau, L) );

    meas.write();
    MeasureBasedOnLanMatrix measPrime(hmatrix);
    TensorHao<double,1> expMTauHPrime = tensor_hao::exp( measPrime.returnLogExpMinusTauModel(tau, L) );

    for(size_t i = 0; i < tau.size(); ++i)
    {
        EXPECT_NEAR( expMTauH(i) , expMTauHPrime(i), 1e-12*abs(expMTauHPrime(i)) );
    }

    int flag=system("rm -rf *.dat");
    if(flag != 0) cout<<"WARNING!!! system command does not exit properly!"<<endl;
}