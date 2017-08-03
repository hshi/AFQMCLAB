//
// Created by boruoshihao on 1/8/17.
//

#include "../include/NiupNidn.h"
#include "../../../../../common/testHao/gtest_custom.h"
#include "../../../../../common/randomHao/include/random_hao.h"

using namespace std;
using namespace tensor_hao;

class NiupNidnTest: public ::testing::Test
{
 public:
    size_t L;
    double dt;
    string decompType;
    tensor_hao::TensorHao<double, 1> U, mu, hx, hy, hz;
    NiupNidn niupNidn;

    NiupNidnTest( )
    {
        L =10;
        dt=0.01;
        decompType="densityCharge";
        U.resize(L); randomFill(U);
        mu.resize(L); randomFill(mu);
        hx.resize(L); randomFill(hx);
        hy.resize(L); randomFill(hy);
        hz.resize(L); randomFill(hz);

        niupNidn = NiupNidn(dt, decompType, U, mu, hx, hy, hz);
    }

    ~NiupNidnTest( )  {}
};

TEST_F(NiupNidnTest, get)
{
    EXPECT_EQ( L, niupNidn.getL() );
    EXPECT_EQ( decompType, niupNidn.getDecompType() );
    EXPECT_EQ( L, niupNidn.getAuxSize() );
    EXPECT_NEAR( dt*U.sum(), niupNidn.getDtUSum(), 1e-12);
}

TEST_F(NiupNidnTest, readForce)
{
    NiupNidnForce force = niupNidn.readForce("randomFileName.dat");
    TensorHao<double,1> forceExact(L); forceExact=0.0;
    EXPECT_FALSE( (diff(force, forceExact, 1e-12)) );
}

TEST_F(NiupNidnTest, logProbOfAuxFromForce)
{
    NiupNidnAux aux(L); for(size_t i = 0; i <L ; ++i) aux(i) = ( uniformHao()>=0 ) ? 1 : -1;
    NiupNidnForce force(L); randomFill(force);

    double logProb = niupNidn.logProbOfAuxFromForce(aux, force);

    double logProbExact(1.0);
    for (size_t i = 0; i < L; ++i)
    {
        logProbExact *= exp( aux(i)*force(i) ) / ( exp( force(i) ) + exp( -force(i) )  ) ;
    }
    logProbExact = log( logProbExact );

    EXPECT_NEAR(logProb, logProbExact, 1e-12);
}