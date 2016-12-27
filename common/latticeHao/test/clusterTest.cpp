#include <fstream>
#include "../include/cluster.h"
#include "../../testHao/gtest_custom.h"
#include "../../readWriteHao/include/readWriteHao.h"

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

TEST(cluster, fileConstructor)
{

    string filename="latt_param.dat";
    size_t L=20;

    writeFile(L, filename); MPIBarrier();
    Cluster cluster(filename);
    removeFile(filename);

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

TEST(cluster, readWriteBcast)
{
    size_t L=9;
    string filename="latt_param.dat";
    Cluster cluster, clusterBase(L);

    if( MPIRank() == 0 ) clusterBase.write(filename);
    if( MPIRank() == 0 ) cluster.read(filename);
    MPIBcast(cluster);

    removeFile(filename);

    EXPECT_EQ(L, cluster.getL());
}
