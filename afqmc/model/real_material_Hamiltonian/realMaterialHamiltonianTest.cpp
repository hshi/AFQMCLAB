//
// Created by boruoshihao on 9/22/16.
//

#include <fstream>
#include "../../../common/testHao/gtest_custom.h"
#include "../../../common/mpiHao/include/mpi_fun.h"
#include "../../../common/tensorHao/include/tensor_all.h"
#include "realMaterialHamiltonian.h"

using namespace std;
using namespace tensor_hao;

class realMaterialHamiltionianTest: public ::testing::Test
{
 public:
    const size_t L=5; const size_t LD = 2*L*L;
    TensorHao<complex<double>, 3> KTensor;
    TensorHao<complex<double>, 4> PTensor;
    TensorHao<complex<double>, 1> DEigen;
    string filename = "model_param";

    realMaterialHamiltionianTest( )
    {
        KTensor = TensorHao<complex<double>, 3>(L, L, 2);
        PTensor = TensorHao<complex<double>, 4>(L, L, 2, LD);
        DEigen  = TensorHao<complex<double>, 1> (LD);
        randomFill(KTensor); randomFill(PTensor); randomFill(DEigen);
        generateInputForModel();
    }

    ~realMaterialHamiltionianTest( )
    {
        removeInputFilenameForModel();
    }

    void generateInputForModel() const
    {
        if(MPIRank() == 0)
        {
            complex<double> data;
            ofstream file;
            file.open(filename, ios_base::out | ios_base::trunc);
            file<<setprecision(16)<<scientific;

            file << setw(26) << KTensor.rank(0) << "\n";

            file << setw(26) << PTensor.rank(3) << "\n";

            for(size_t i = 0; i < KTensor.size(); ++i)
            {
                data = KTensor.data()[i];
                file<<setw(26)<<data.real()<<setw(26)<<data.imag()<<"\n";
            }

            for(size_t i = 0; i < PTensor.size(); ++i)
            {
                data = PTensor.data()[i];
                file<<setw(26)<<data.real()<<setw(26)<<data.imag()<<"\n";
            }

            for(size_t j = 0; j < DEigen.size() ; ++j)
            {
                data = DEigen.data()[j];
                file<<setw(26)<<data.real()<<setw(26)<<data.imag()<<"\n";
            }
            file.close();
        }

        MPIBarrier();
    }

    void removeInputFilenameForModel()
    {
        int rank = MPIRank();
        if(rank==0) remove( filename.c_str() );
        MPIBarrier();
    }
};

TEST_F(realMaterialHamiltionianTest, readfileConstructor)
{
    RealMaterialHamiltonian H(filename);
    EXPECT_EQ(L, H.getBasisSize());
    EXPECT_EQ(LD, H.getInteractionSize());
    EXPECT_FALSE( diff(KTensor, H.getKTensor(), 1e-12) );
    EXPECT_FALSE( diff(PTensor, H.getPTensor(), 1e-12) );
    EXPECT_FALSE( diff(DEigen,  H.getDEigen(), 1e-12) );
}

TEST_F(realMaterialHamiltionianTest, copyConstructor)
{
    RealMaterialHamiltonian HBase(filename);
    RealMaterialHamiltonian H(HBase);
    EXPECT_EQ(L, H.getBasisSize());
    EXPECT_EQ(LD, H.getInteractionSize());
    EXPECT_FALSE( diff(KTensor, H.getKTensor(), 1e-12) );
    EXPECT_FALSE( diff(PTensor, H.getPTensor(), 1e-12) );
    EXPECT_FALSE( diff(DEigen,  H.getDEigen(), 1e-12) );
}

TEST_F(realMaterialHamiltionianTest, moveConstructor)
{
    RealMaterialHamiltonian HBase(filename);
    RealMaterialHamiltonian H( move(HBase) );
    EXPECT_EQ(L, H.getBasisSize());
    EXPECT_EQ(LD, H.getInteractionSize());
    EXPECT_FALSE( diff(KTensor, H.getKTensor(), 1e-12) );
    EXPECT_FALSE( diff(PTensor, H.getPTensor(), 1e-12) );
    EXPECT_FALSE( diff(DEigen,  H.getDEigen(), 1e-12) );
}

TEST_F(realMaterialHamiltionianTest, copyAssignment)
{
    RealMaterialHamiltonian HBase(filename);
    RealMaterialHamiltonian H; H = HBase;
    EXPECT_EQ(L, H.getBasisSize());
    EXPECT_EQ(LD, H.getInteractionSize());
    EXPECT_FALSE( diff(KTensor, H.getKTensor(), 1e-12) );
    EXPECT_FALSE( diff(PTensor, H.getPTensor(), 1e-12) );
    EXPECT_FALSE( diff(DEigen,  H.getDEigen(), 1e-12) );
}

TEST_F(realMaterialHamiltionianTest, moveAssignment)
{
    RealMaterialHamiltonian HBase(filename);
    RealMaterialHamiltonian H; H = move( HBase );
    EXPECT_EQ(L, H.getBasisSize());
    EXPECT_EQ(LD, H.getInteractionSize());
    EXPECT_FALSE( diff(KTensor, H.getKTensor(), 1e-12) );
    EXPECT_FALSE( diff(PTensor, H.getPTensor(), 1e-12) );
    EXPECT_FALSE( diff(DEigen,  H.getDEigen(), 1e-12) );
}