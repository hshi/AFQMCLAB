#include <iostream>
#include "../include/random_hao.h"
#include "../../testHao/gtest_custom.h"

using namespace std;

TEST(random_number, check_point)
{
    int L=10; int L_check=5;
    double ran[L],ran_check[L];

    randomHaoInit();
    for(int i=0;i<L;i++) ran[i]= uniformHao();

    randomHaoInit();
    for(int i=0;i<L_check;i++) ran_check[i]= uniformHao();
    randomHaoSave();
    for(int i=0; i<100; i++) uniformHao();
    randomHaoInit(-1, 1);  // it is the same with: randomHaoRead();
    for(int i=L_check;i<L;i++) ran_check[i]= uniformHao();

    EXPECT_POINTER_DOUBLE_EQ(L, ran, ran_check);

    int rank=MPIRank();
    string filename="random_checkpoint_"+ to_string(rank) +".dat";
    remove( filename.c_str() );
}

TEST(random_number, uniform)
{
    int L=1000000;
    int incircle=0;
    double pi;
    for(int i=0; i<L; i++)
    {
        double x= uniformHao();
        double y= uniformHao();
        if((x*x+y*y)<=1.0) incircle++;
    }
    pi = (incircle*4.0)/(L*1.0);
    pi = MPISum(pi) / ( 1.0* MPISize() );
    if( MPIRank() == 0 )
    {
        EXPECT_NEAR(pi, 3.14159, 0.01);
    }
}

TEST(random_number, gaussian)
{
    int L=1000000;
    double mean=0; double var=0;
    for(int i=0; i<L; i++)
    {
        double tmp= gaussianHao();
        mean+=tmp;
        var+=tmp*tmp;
    }
    mean/=L; var/=L;
    mean = MPISum( mean ) / MPISize();
    var  = MPISum( var )  / MPISize();
    if( MPIRank() == 0 )
    {
        EXPECT_NEAR(mean, 0, 0.01);
        EXPECT_NEAR(var, 1, 0.01);
    }
}