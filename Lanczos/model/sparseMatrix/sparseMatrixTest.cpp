//
// Created by boruoshihao on 10/26/16.
//

#include "../../../libhao/test_hao/gtest_custom.h"
#include "../../interface/include/Lanczos.h"
#include "sparseMatrix.h"

using namespace std;
using namespace tensor_hao;

class lanczosModelSparseMatrixTest: public ::testing::Test
{
 public:
    const size_t L = 30;
    vector<SparseElement> Hm;
    TensorHao<double,1> Hv;
    lanczosModelSparseMatrixTest( )
    {
        TensorHao<complex<double>, 2 > matrix(L,L);
        randomFill(matrix); matrix += conjtrans(matrix);
        for(size_t i = 0; i < L; ++i)
        {
            for(size_t j = 0; j < L; ++j)
            {
                if( abs( matrix(i,j) ) > 0.5  ) Hm.push_back( { i,j, matrix(i,j) } );
                else matrix(i,j)=0.0;
            }
        }

        Hv.resize(L); eigen_cpu( matrix, Hv);
    }

    ~lanczosModelSparseMatrixTest( )
    {
    }
};

TEST_F(lanczosModelSparseMatrixTest, voidConstructor)
{
    SparseMatrix sm;
    EXPECT_EQ( 0, sm.getWfSize() );
    EXPECT_EQ( 0, sm.getHm().size() );
}

TEST_F(lanczosModelSparseMatrixTest, copyConstructor)
{
    SparseMatrix sm(L, Hm);

    EXPECT_EQ( L, sm.getWfSize() );
    vector<SparseElement> smHm = sm.getHm();
    for(size_t i = 0; i < smHm.size(); ++i)
    {
        EXPECT_EQ( Hm[i].i, smHm[i].i );
        EXPECT_EQ( Hm[i].j, smHm[i].j );
        EXPECT_COMPLEXDOUBLE_EQ( Hm[i].h, smHm[i].h );
    }
}

TEST_F(lanczosModelSparseMatrixTest, moveConstructor)
{
    vector<SparseElement> HmTemp(Hm);
    SparseMatrix sm( L, move(HmTemp) );

    EXPECT_FALSE( HmTemp.data() );
    EXPECT_EQ( L, sm.getWfSize() );
    vector<SparseElement> smHm = sm.getHm();
    for(size_t i = 0; i < smHm.size(); ++i)
    {
        EXPECT_EQ( Hm[i].i, smHm[i].i );
        EXPECT_EQ( Hm[i].j, smHm[i].j );
        EXPECT_COMPLEXDOUBLE_EQ( Hm[i].h, smHm[i].h );
    }
}

TEST_F(lanczosModelSparseMatrixTest, readWrite)
{
    SparseMatrix smp( L, Hm ), sm;
    smp.write("sparseMatrix.dat");
    sm.read("sparseMatrix.dat");

    EXPECT_EQ( L, sm.getWfSize() );
    vector<SparseElement> smHm = sm.getHm();
    for(size_t i = 0; i < smHm.size(); ++i)
    {
        EXPECT_EQ( Hm[i].i, smHm[i].i );
        EXPECT_EQ( Hm[i].j, smHm[i].j );
        EXPECT_COMPLEXDOUBLE_EQ( Hm[i].h, smHm[i].h );
    }
}

TEST_F(lanczosModelSparseMatrixTest, lanczos)
{
    SparseMatrix sm(L, Hm); Lanczos lan( sm );
    lan.findEigen(1);

    EXPECT_NEAR( Hv(0), lan.getEigenvalue(0), 1e-10 );
}