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
        K.resize(L,L); randomFill(K); K+=trans(K);
        choleskyVecs.resize(L, L, choleskyNumber); randomFill(choleskyVecs);
        for(size_t i = 0; i < choleskyNumber; ++i) choleskyVecs[i] += trans(choleskyVecs[i]);
        choleskyBg.resize(choleskyNumber); randomFill(choleskyBg);
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
}