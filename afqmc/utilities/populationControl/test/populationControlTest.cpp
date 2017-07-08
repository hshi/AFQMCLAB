//
// Created by boruoshihao on 1/13/17.
//

#include "../../../../common/testHao/gtest_custom.h"
#include "../../../../common/randomHao/include/random_hao.h"
#include "../include/populationControl.h"
#include "doublePopType.h"

using namespace std;

TEST(populationControlTest, check)
{
    int L=10; vector<double> a(L); double ratio, average;

    for(int i=0; i<L; i++) a[i]=i+1.0;
    tie(ratio,average) = popCheck(a);
    EXPECT_DOUBLE_EQ(ratio, 5.5);
    EXPECT_DOUBLE_EQ(average, 5.5);

    for(int i=0; i<L; i++) a[i]=1.0; a[5] =6.0;
    tie(ratio,average) = popCheck(a);
    EXPECT_DOUBLE_EQ(ratio, 4.0);
    EXPECT_DOUBLE_EQ(average, 1.5);
}

TEST(populationControlTest, configuration)
{
    randomHaoInit(985456376,1);
    int L=100; int size=4;
    vector<double> a(L); for(int i=0; i<L; i++) a[i]=i+1.0;

    if(MPIRank()==0)
    {
        vector<int> b_exact(L); //Exact results from old fortran code
        b_exact={60,62,66,69,71,73,75,8,77,80,82,82,13,14,84,85,87,88,90,20,92,22,23,92,25,32,44,28,93,30,94,32,96,34,
                 35,97,37,38,39,40,98,42,99,44,45,100,47,48,49,50,51,52,53,53,55,56,57,58,59,60,55,62,63,64,65,66,67,68,
                 69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100};
        for(int i = 0; i <L ; i++) b_exact[i]--;
        vector<int> b=popConfiguration(size, a);
        EXPECT_VECOTR_EQ(b_exact, b);
    }
}

TEST(populationControlTest, doublePopulationControl)
{
    randomHaoInit(0,1);

    int rank=MPIRank(); int size=MPISize();
    int L_chunk=100; int L=L_chunk*size;
    vector<double> walker(L_chunk);
    vector<int> table;

    //Set walker
    for(int i=0; i<L_chunk; i++) walker[i]=1.0*i+rank*L_chunk;

    if(rank==0)
    {
        //Random set weight
        vector<double> weight(L); for(int i=0; i<L; i++) weight[i]=5.0*uniformHao();
        table=popConfiguration(size,weight);
        //for(int i=0; i<L; i++) cout<<table[i]<<" "; cout<<endl;
    }

    vector<DoublePop> walkerPop;
    walkerPop.reserve(L_chunk); for(int i=0; i<L_chunk; i++) walkerPop.push_back( DoublePop(walker[i]) );
    populationControl(walkerPop, table);

    vector<double> walker_gather; if(rank==0) walker_gather.resize(L);
#ifdef MPI_HAO
    MPI_Gather(walker.data(), L_chunk, MPI_DOUBLE, walker_gather.data(), L_chunk, MPI_DOUBLE, 0, MPI_COMM_WORLD);
#else
    walker_gather=walker;
#endif

    if(rank==0)
    {
        vector<double> walker_gather_exact(L);
        for(int i = 0; i <L ; ++i) walker_gather_exact[i] = table[i];
        EXPECT_VECOTR_DOUBLE_EQ( walker_gather_exact, walker_gather);
    }
}