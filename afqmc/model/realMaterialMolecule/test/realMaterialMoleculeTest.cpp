//
// Created by boruoshihao on 5/30/17.
//
#include "../include/realMaterialMolecule.h"

using namespace std;
using namespace H5;
using namespace tensor_hao;

class RealMaterialMoleculeTest: public ::testing::Test
{
 public:
    size_t L, Nup, Ndn;
    size_t choleskyNumber;
    TensorHao<double, 2> t, K;
    TensorHao<double, 3> choleskyVecs;
    TensorHao<double, 1> choleskyBg;
    string filename;

    RealMaterialMoleculeTest( )
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

    ~RealMaterialMoleculeTest( )
    {
        removeFile(filename);
    }
};

TEST_F(RealMaterialMoleculeTest, voidConstructor)
{
    RealMaterialMolecule realMaterialMolecule;
    EXPECT_EQ( static_cast<size_t>(0), realMaterialMolecule.getL() );
    EXPECT_EQ( static_cast<size_t>(0), realMaterialMolecule.getNup() );
    EXPECT_EQ( static_cast<size_t>(0), realMaterialMolecule.getNdn() );
}

TEST_F(RealMaterialMoleculeTest, readWriteBcast)
{
    string filenamePrime="modelPrime.h5";
    RealMaterialMolecule realMaterialMoleculeBase(filename), realMaterialMolecule;

    if( MPIRank()==0 ) realMaterialMoleculeBase.write(filenamePrime);
    MPIBarrier();

    if( MPIRank() == 0 ) realMaterialMolecule.read(filenamePrime);
    MPIBcast( realMaterialMolecule );

    EXPECT_EQ( L, realMaterialMolecule.getL() );
    EXPECT_EQ( Nup, realMaterialMolecule.getNup() );
    EXPECT_EQ( Ndn, realMaterialMolecule.getNdn() );
    EXPECT_EQ( choleskyNumber, realMaterialMolecule.getCholeskyNumber() );
    EXPECT_FALSE( diff(t, realMaterialMolecule.getT(), 1e-12) );
    EXPECT_FALSE( diff(K, realMaterialMolecule.getK(), 1e-12) );
    EXPECT_FALSE( diff(choleskyVecs, realMaterialMolecule.getCholeskyVecs(), 1e-12) );
    EXPECT_FALSE( diff(choleskyBg, realMaterialMolecule.getCholeskyBg(), 1e-12) );
    EXPECT_EQ( static_cast<size_t>(0), realMaterialMolecule.getKpEigenStatus() );

    removeFile(filenamePrime);
}

TEST_F(RealMaterialMoleculeTest, writeBackGround)
{
    string filenamePrime="modelPrime.h5";
    TensorHao<double,1> background(choleskyNumber); randomFill(background); MPIBcast(background);

    if( MPIRank()==0 )
    {
        RealMaterialMolecule realMaterialMoleculeBase(filename);
        realMaterialMoleculeBase.write(filenamePrime);
        realMaterialMoleculeBase.updateBackGround(background);
        realMaterialMoleculeBase.writeBackGround(filenamePrime);
    }
    MPIBarrier();

    RealMaterialMolecule realMaterialMolecule(filenamePrime);
    EXPECT_FALSE( diff(background, realMaterialMolecule.getCholeskyBg(), 1e-12) );

    removeFile(filenamePrime);
}

TEST_F(RealMaterialMoleculeTest, updateBackGround)
{
    RealMaterialMolecule realMaterialMolecule(filename);
    EXPECT_EQ( static_cast<size_t>(0), realMaterialMolecule.getKpEigenStatus() );

    Hop2is Hop2is = realMaterialMolecule.returnExpMinusAlphaK(0.01);
    EXPECT_EQ( static_cast<size_t>(2), realMaterialMolecule.getKpEigenStatus() );

    TensorHao<double> background(choleskyNumber); randomFill(background);
    TensorHao<double> backgroundPrime(background);
    realMaterialMolecule.updateBackGround( move(backgroundPrime) );
    EXPECT_EQ( static_cast<size_t>(0), realMaterialMolecule.getKpEigenStatus() );

    EXPECT_FALSE( diff(background, realMaterialMolecule.getCholeskyBg(), 1e-12 ) );
    EXPECT_TRUE( diff(background, backgroundPrime, 1e-12) );
}

TEST_F(RealMaterialMoleculeTest, returnLogExpMinusAlphaK)
{
    RealMaterialMolecule realMaterialMolecule(filename);
    double dt=0.05;

    complex<double> logw(0,0);
    for(size_t i = 0; i < choleskyNumber; ++i) logw += choleskyBg(i)*choleskyBg(i);
    logw *= 0.5*dt;

    TensorHao<complex<double>,2> matrix(L,L);
    for(size_t i = 0; i < L; ++i)
    {
        for(size_t j = 0; j < L; ++j) matrix(j,i) += K(j,i);
    }
    for(size_t k = 0; k < choleskyNumber; ++k)
    {
        for(size_t i = 0; i < L; ++i)
        {
            for(size_t j = 0; j < L; ++j)
            {
                matrix(j,i) += choleskyBg(k)*choleskyVecs(j,i,k);
            }
        }
    }
    matrix=complex<double>(-dt)*matrix;

    LogHop2is logHop2is = realMaterialMolecule.returnLogExpMinusAlphaK(dt);

    EXPECT_EQ( static_cast<size_t>(1), realMaterialMolecule.getKpEigenStatus() );
    EXPECT_EQ( logw, logHop2is.logw );
    EXPECT_FALSE( diff(matrix, logHop2is.matrix, 1e-12 ) );
}

TEST_F(RealMaterialMoleculeTest, returnExpMinusAlphaK)
{
    RealMaterialMolecule realMaterialMolecule(filename);
    double dt=0.05;

    complex<double> logw(0,0);
    for(size_t i = 0; i < choleskyNumber; ++i) logw += choleskyBg(i)*choleskyBg(i);
    logw *= 0.5*dt;

    TensorHao<complex<double>,2> matrix(L,L);
    for(size_t i = 0; i < L; ++i)
    {
        for(size_t j = 0; j < L; ++j) matrix(j,i) += K(j,i);
    }
    for(size_t k = 0; k < choleskyNumber; ++k)
    {
        for(size_t i = 0; i < L; ++i)
        {
            for(size_t j = 0; j < L; ++j)
            {
                matrix(j,i) += choleskyBg(k)*choleskyVecs(j,i,k);
            }
        }
    }
    matrix=complex<double>(-dt)*matrix;

    TensorHao<complex<double>,2> eigenVec( matrix );
    TensorHao<double,1> eigenVal(L);
    eigen_cpu(eigenVec, eigenVal);
    gmm_cpu( eigenVec, dMultiMatrix( exp(eigenVal), trans(eigenVec) ), matrix );


    Hop2is Hop2is = realMaterialMolecule.returnExpMinusAlphaK(dt);

    EXPECT_EQ( static_cast<size_t>(2), realMaterialMolecule.getKpEigenStatus() );
    EXPECT_EQ( logw, Hop2is.logw );
    EXPECT_FALSE( diff(matrix, Hop2is.matrix, 1e-12 ) );
}

TEST_F(RealMaterialMoleculeTest, returnExpMinusAlphaV)
{
    RealMaterialMolecule realMaterialMolecule(filename);
    double dt=0.05;
    CholeskyReal choleskyReal=realMaterialMolecule.returnExpMinusAlphaV(dt);

    EXPECT_EQ( dt, choleskyReal.getDt() );
    EXPECT_EQ( choleskyReal.getCholeskyBg(), &realMaterialMolecule.getCholeskyBg() );
    EXPECT_EQ( choleskyNumber, choleskyReal.getCholeskyNumber() );
}