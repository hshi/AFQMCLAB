//
// Created by boruoshihao on 6/5/17.
//
#include "../include/realMaterialMoleculeMeasureFixedSD2sSD2is.h"

using namespace std;
using namespace H5;
using namespace tensor_hao;

class realMaterialMoleculeFixedSD2sSD2isTest: public ::testing::Test
{
 public:
    size_t L, Nup, Ndn;
    size_t choleskyNumber;
    TensorHao<double, 2> t, K;
    TensorHao<double, 3> choleskyVecs;
    TensorHao<double, 1> choleskyBg;
    string filename;

    RealMaterialMolecule model;
    SD2s walkerLeft;
    SD2is walkerRight;

    realMaterialMoleculeFixedSD2sSD2isTest( )
    {
        L=5; Nup=3; Ndn=2; choleskyNumber=6;
        t.resize(L,L); randomFill(t); t+=trans(t);
        choleskyVecs.resize(L, L, choleskyNumber); randomFill(choleskyVecs);
        for(size_t i = 0; i < choleskyNumber; ++i) choleskyVecs[i] += trans(choleskyVecs[i]);
        choleskyBg.resize(choleskyNumber); randomFill(choleskyBg);

        K.resize(L,L); K=0.0; double tmp;
        for(size_t g = 0; g < choleskyNumber; ++g)
        {
            for(size_t i = 0; i < L ; ++i)
            {
                for(size_t j = 0; j < L ; ++j)
                {
                    tmp = 0.0; for(size_t k = 0; k < L ; ++k) tmp += choleskyVecs(k,j,g) * choleskyVecs(k,i,g);
                    K(j,i) += tmp;
                }
            }
        }
        K = t - K * 0.5;
        filename="model.h5"; writeHdf5();

        if( MPIRank()==0 ) model.read(filename);
        MPIBcast(model);

        walkerLeft.resize(L, Nup, Ndn); walkerLeft.randomFill();
        walkerRight.resize(L, Nup, Ndn); walkerRight.randomFill();
    }

    void writeHdf5()
    {
        if( MPIRank()==0 )
        {
            H5File file(filename, H5F_ACC_TRUNC);
            writeFile( L, file, "L" );
            writeFile( Nup, file, "Nup" );
            writeFile( Ndn, file, "Ndn" );
            writeFile( choleskyNumber, file, "choleskyNumber" );
            writeFile( t.size(),  t.data(),  file, "t" );
            writeFile( K.size(),  K.data(),  file, "K" );
            writeFile( choleskyVecs.size(), choleskyVecs.data(), file, "choleskyVecs");
            writeFile( choleskyBg.size(), choleskyBg.data(), file, "choleskyBg");
            file.close();
        }
        MPIBarrier();
    }

    ~realMaterialMoleculeFixedSD2sSD2isTest( )
    {
        removeFile(filename);
    }
};

TEST_F(realMaterialMoleculeFixedSD2sSD2isTest, returnEnergy)
{
    RealMaterialMoleculeMeasureFixedSD2sSD2is meas(model, walkerLeft);
    SD2sSD2isOperation walkerWalkerOperation(walkerLeft, walkerRight);
    meas.addMeasurement(walkerWalkerOperation, 1.0);

    const TensorHao<complex<double>, 2 > &greenUp = walkerWalkerOperation.returnGreenMatrixUp();
    const TensorHao<complex<double>, 2 > &greenDn = walkerWalkerOperation.returnGreenMatrixDn();

    complex<double> TEnergy(0,0);
    for(size_t i = 0; i < L; ++i)
    {
        for(size_t j = 0; j < L; ++j)
        {
            TEnergy += t(j,i) * ( greenUp(j,i)+greenDn(j,i) );
        }
    }

    complex<double> bgEnergy(0,0);
    complex<double> temp;
    for(size_t k = 0; k < choleskyNumber; ++k)
    {
        temp = 0.0;
        for(size_t i = 0; i < L ; ++i)
        {
            for(size_t j = 0; j < L; ++j)
            {
                temp += choleskyVecs(j,i,k) * ( greenUp(j,i)+greenDn(j,i) );
            }
        }
        bgEnergy += temp * temp * 0.5;
    }

    complex<double> exEnergy(0,0);
    for(size_t g = 0; g < choleskyNumber; ++g)
    {
        for(size_t i = 0;  i< L ; i++)
        {
            for(size_t j = 0; j < L; ++j)
            {
                for(size_t k = 0; k < L; ++k)
                {
                    for(size_t l = 0; l < L; ++l)
                    {
                        exEnergy += choleskyVecs(l,i,g)*choleskyVecs(k,j,g)*( greenUp(i,k)*greenUp(j,l) + greenDn(i,k)*greenDn(j,l) );
                    }
                }
            }
        }
    }
    exEnergy *= 0.5;

    complex<double> Henergy= TEnergy +bgEnergy-exEnergy;
    MPIBcast(Henergy);

    EXPECT_COMPLEX_NEAR( Henergy, meas.returnEnergy(), 1e-12 );
}

TEST_F(realMaterialMoleculeFixedSD2sSD2isTest, getForce)
{
    double dt=0.01; double cap=0.21;
    RealMaterialMoleculeMeasureFixedSD2sSD2is meas(model, walkerLeft);
    SD2sSD2isOperation walkerWalkerOperation(walkerLeft, walkerRight);
    CholeskyReal twoBody=model.returnExpMinusAlphaV(dt);
    CholeskyRealForce force = meas.getForce(twoBody, walkerWalkerOperation, cap);
    MPIBcast(force);

    const TensorHao<complex<double>, 2 > &greenUp = walkerWalkerOperation.returnGreenMatrixUp();
    const TensorHao<complex<double>, 2 > &greenDn = walkerWalkerOperation.returnGreenMatrixDn();

    TensorHao<complex<double>,1> forceExact(choleskyNumber); complex<double> tmp;
    for(size_t k = 0; k < choleskyNumber; ++k)
    {
        tmp = 0.0;
        for(size_t i = 0; i < L ; ++i)
        {
            for(size_t j = 0; j < L; ++j)
            {
                tmp += choleskyVecs(j,i,k) * ( greenUp(j,i)+greenDn(j,i) );
            }
        }
        tmp -= choleskyBg(k);
        tmp *= twoBody.getSqrtMinusDt();

        if( abs(tmp) > cap ) forceExact(k) = tmp/abs(tmp) * cap;
        else forceExact(k)=tmp;
    }
    MPIBcast(forceExact);

    EXPECT_FALSE( diff(force, forceExact, 1e-12) );
}
