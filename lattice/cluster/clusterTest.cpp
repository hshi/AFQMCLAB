#include <fstream>
#include "cluster.h"
#include "../../libhao/test_hao/gtest_custom.h"
#include "../../libhao/mpi_hao/mpi_fun.h"

using namespace std;

TEST(cluster, voidConstructor)
{
    Cluster cluster;
    EXPECT_EQ( static_cast<size_t>(0), cluster.getL());
}

TEST(cluster, LConstructor)
{
    size_t L=9;
    Cluster cluster(L);
    EXPECT_EQ(L, cluster.getL());
}

void generateInputForCluster(const string& filename, size_t L)
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
    size_t L=20;

    generateInputForCluster(filename, L);

    Cluster cluster(filename);

    removeInputFilenameForCluster(filename);

    EXPECT_EQ( L, cluster.getL() );
}

TEST(cluster, equalConstructor)
{
    size_t L=9;
    Cluster clusterBase(L);
    Cluster cluster(clusterBase);
    EXPECT_EQ(L, cluster.getL());
}

TEST(cluster, moveConstructor)
{
    size_t L=9;
    Cluster cluster = Cluster(L);
    EXPECT_EQ(L, cluster.getL());
}

TEST(cluster, equalAssignment)
{
    size_t L=9;
    Cluster clusterBase(L);
    Cluster cluster; cluster = clusterBase;
    EXPECT_EQ(L, cluster.getL());
}

TEST(cluster, moveAssignment)
{
    size_t L=9;
    Cluster clusterBase(L);
    Cluster cluster; cluster = move( clusterBase );
    EXPECT_EQ(L, cluster.getL());
}
