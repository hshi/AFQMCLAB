//
// Created by boruoshihao on 11/18/16.
//

#include "../../../../libhao/testHao/gtest_custom.h"
#include "../../../interface/include/LanczosInterface.h"
#include "../../../../libhao/mathHao/include/simple_fun.h"
#include "../include/SpinlessFermions.h"

using namespace std;
using namespace tensor_hao;

TEST(SpinlessFermionsTest, readWrite)
{
    size_t L(10), N(5);
    vector<LanOneBody> K(8);
    vector<LanTwoBody> V(4);

    for(size_t i = 0; i < K.size(); ++i) K[i] = { i, i+1, complex<double>(i+2, i+3) };
    for(size_t i = 0; i < V.size(); ++i) V[i] = { i, i+1, i+2, i+3, complex<double>(i+4, i+5)  };

    SpinlessFermions H(L, N);
    H.setK(K); H.setV(V);

    string filename = "SpinlessFermions.dat";
    H.write(filename);

    SpinlessFermions HNew(filename);
    EXPECT_EQ( L, HNew.getL()   );
    EXPECT_EQ( N, HNew.getN() );
    EXPECT_EQ( binomialCoeff(L,N), HNew.getWfSize() );

    for(size_t m = 0; m < K.size(); ++m)
    {
        EXPECT_EQ( K[m].i, HNew.getK()[m].i);
        EXPECT_EQ( K[m].j, HNew.getK()[m].j);
        EXPECT_COMPLEXDOUBLE_EQ( K[m].K, HNew.getK()[m].K);
    }

    for(size_t m = 0; m < V.size(); ++m)
    {
        EXPECT_EQ( V[m].i, HNew.getV()[m].i);
        EXPECT_EQ( V[m].j, HNew.getV()[m].j);
        EXPECT_EQ( V[m].k, HNew.getV()[m].k);
        EXPECT_EQ( V[m].l, HNew.getV()[m].l);
        EXPECT_COMPLEXDOUBLE_EQ( V[m].V, HNew.getV()[m].V);
    }

    remove( filename.c_str() );
}