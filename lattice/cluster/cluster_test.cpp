#include <fstream>
#include "cluster.h"
#include "../../libhao/test_hao/gtest_custom.h"
#include "../../libhao/mpi_hao/mpi_fun.h"

using namespace std;

TEST(cluster, voidConstructor)
{
    Cluster cluster;
    EXPECT_EQ(0, cluster.getL());
}

TEST(cluster, LConstructor)
{
    int L=9;
    Cluster cluster(L);
    EXPECT_EQ(L, cluster.getL());
}

void generateInputForCluster(const string& filename, int L)
{
    int rank = MPIRank();
    if(rank==0)
    {
        ofstream file;
        file.open(filename, ios::out|ios::trunc);
        file<<L<<"\n";
        file.close();
    }
    MPIBarrier();
}

void removeInputFilenameForCluster(const string &filename)
{
    int rank = MPIRank();
    if(rank==0) remove( filename.c_str() );
    MPIBarrier();
}

TEST(cluster, fileConstructor)
{

    string filename="latt_param.dat";
    int L=20;

    generateInputForCluster(filename, L);

    Cluster cluster(filename);

    removeInputFilenameForCluster(filename);

    EXPECT_EQ( L, cluster.getL() );
}

TEST(cluster, equalConstructor)
{
    int L=9;
    Cluster clusterBase(L);
    Cluster cluster(clusterBase);
    EXPECT_EQ(L, cluster.getL());
}

TEST(cluster, moveConstructor)
{
    int L=9;
    Cluster cluster = Cluster(L);
    EXPECT_EQ(L, cluster.getL());
}

TEST(cluster, equalAssignment)
{
    int L=9;
    Cluster clusterBase(L);
    Cluster cluster; cluster = clusterBase;
    EXPECT_EQ(L, cluster.getL());
}

TEST(cluster, moveAssignment)
{
    int L=9;
    Cluster clusterBase(L);
    Cluster cluster; cluster = move( clusterBase );
    EXPECT_EQ(L, cluster.getL());
}