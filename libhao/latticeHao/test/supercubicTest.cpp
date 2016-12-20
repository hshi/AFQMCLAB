//
// Created by boruoshihao on 12/20/16.
//
#include <fstream>
#include "../include/supercubic.h"
#include "../../testHao/gtest_custom.h"
#include "../../mpiHao/include/mpi_fun.h"
#include "../../readWriteHao/include/readWriteHao.h"

using namespace std;
using namespace tensor_hao;

TEST(supercubicTest, voidConstructor)
{
    Supercubic latt;
    EXPECT_EQ( static_cast<size_t>(0), latt.getDimen() );
    EXPECT_EQ( static_cast<size_t>(0), latt.getL() );
}

TEST(supercubicTest, tensorConstructor)
{
    TensorHao<int,1> n(3); n = {2,3,4};
    Supercubic latt(n);
    EXPECT_FALSE( diff( n, latt.getN(), 0.0 ) );
    EXPECT_EQ( n.size(), latt.getDimen() );
    EXPECT_EQ( static_cast<size_t>(24), latt.getL() );
}

TEST(supercubicTest, readConstructor)
{
    TensorHao<int,1> n(3); n = {3,5,6};

    string filename="latt_file.dat";
    if( MPIRank()== 0 )
    {
        ofstream file;
        file.open(filename, ios::out|ios::trunc);
        file<<n.size()<<"\n";
        for(size_t i=0; i<n.size();i++) { file<<n(i)<<" "; } file<<"\n";
        file.close();
    }

    Supercubic latt( filename ); removeFile(filename);
    EXPECT_FALSE( diff( n, latt.getN(), 0.0 ) );
    EXPECT_EQ( n.size(), latt.getDimen() );
    EXPECT_EQ( static_cast<size_t>(90), latt.getL() );
}

TEST(supercubicTest, copyConstructor)
{
    TensorHao<int,1> n(3); n = {2,3,4};
    Supercubic latt_old(n), latt(latt_old);
    EXPECT_FALSE( diff( n, latt.getN(), 0.0 ) );
    EXPECT_EQ( n.size(), latt.getDimen() );
    EXPECT_EQ( static_cast<size_t>(24), latt.getL() );
}

TEST(supercubicTest, moveConstructor)
{
    TensorHao<int,1> n(3); n = {2,3,4};
    Supercubic latt_old(n), latt( move(latt_old) );

    EXPECT_FALSE( latt_old.getN().data() );

    EXPECT_FALSE( diff( n, latt.getN(), 0.0 ) );
    EXPECT_EQ( n.size(), latt.getDimen() );
    EXPECT_EQ( static_cast<size_t>(24), latt.getL() );
}

TEST(supercubicTest, copyAssignment)
{
    TensorHao<int,1> n(3); n = {2,3,4};
    Supercubic latt_old(n), latt; latt = latt_old;
    EXPECT_FALSE( diff( n, latt.getN(), 0.0 ) );
    EXPECT_EQ( n.size(), latt.getDimen() );
    EXPECT_EQ( static_cast<size_t>(24), latt.getL() );
}

TEST(supercubicTest, moveAssignment)
{
    TensorHao<int,1> n(3); n = {2,3,4};
    Supercubic latt_old(n), latt; latt = move(latt_old);

    EXPECT_FALSE( latt_old.getN().data() );

    EXPECT_FALSE( diff( n, latt.getN(), 0.0 ) );
    EXPECT_EQ( n.size(), latt.getDimen() );
    EXPECT_EQ( static_cast<size_t>(24), latt.getL() );
}

TEST(supercubicTest, coor)
{
    TensorHao<int,1> n(3); n = {3,5,6};
    Supercubic latt(n);

    TensorHao<int, 1> coor;
    int ix(0), iy(0), iz(0);
    for(size_t i = 0; i < latt.getL(); ++i)
    {
        coor = latt.coor(i);
        EXPECT_EQ( coor(0), ix );
        EXPECT_EQ( coor(1), iy );
        EXPECT_EQ( coor(2), iz );

        ix++;
        if(ix==3) {ix=0;iy++;}
        if(iy==5) {iy=0;iz++;}
    }
}

TEST(supercubicTest, index)
{
    TensorHao<int,1> n(3); n = {3,5,6};
    Supercubic latt(n);
    TensorHao<int, 1> coor;
    for(size_t i = 0; i < latt.getL(); ++i)
    {
        coor = latt.coor(i);
        EXPECT_EQ( static_cast<int>(i), latt.index(coor) );
    }
}

TEST(supercubicTest, bound)
{
    TensorHao<int,1> n(3); n = {3,5,6};
    Supercubic latt(n);

    EXPECT_EQ( latt.bound(-5,7),  2 );
    EXPECT_EQ( latt.bound(-7,7),  0 );
    EXPECT_EQ( latt.bound(-10,7), 4 );
    EXPECT_EQ( latt.bound(-14,7), 0 );
    EXPECT_EQ( latt.bound(-22,7), 6 );
    EXPECT_EQ( latt.bound(5,7),   5 );
    EXPECT_EQ( latt.bound(7,7),   0 );
    EXPECT_EQ( latt.bound(10,7),  3 );
    EXPECT_EQ( latt.bound(14,7),  0 );
    EXPECT_EQ( latt.bound(22,7),  1 );
}

TEST(supercubicTest, coor_relat)
{
    TensorHao<int,1> n(2); n = {3,4};
    Supercubic latt(n);

    TensorHao<int, 1> coor_i(2),coor_j(2),dist(2),dist_exact(2);

    coor_i={1,2};coor_j={2,3};dist_exact={1,1};
    dist=latt.coor_relat(coor_i,coor_j);
    EXPECT_FALSE( diff(dist, dist_exact, 0.0) );

    coor_i={2,3};coor_j={1,2};dist_exact={2,3};
    dist=latt.coor_relat(coor_i,coor_j);
    EXPECT_FALSE( diff(dist, dist_exact, 0.0) );

    coor_i={1,2};coor_j={2,0};dist_exact={1,2};
    dist=latt.coor_relat(coor_i,coor_j);
    EXPECT_FALSE( diff(dist, dist_exact, 0.0) );
}

TEST(supercubicTest, coor_abs_relat)
{
    TensorHao<int,1> n(2); n = {3,4};
    Supercubic latt(n);

    TensorHao<int, 1> coor_i(2),coor_j(2),dist(2),dist_exact(2);

    coor_i={1,2};coor_j={2,3};dist_exact={1,1};
    dist=latt.coor_abs_relat(coor_i,coor_j);
    EXPECT_FALSE( diff(dist, dist_exact, 0.0) );

    coor_i={2,3};coor_j={1,2};dist_exact={1,1};
    dist=latt.coor_abs_relat(coor_i,coor_j);
    EXPECT_FALSE( diff(dist, dist_exact, 0.0) );

    coor_i={1,2};coor_j={2,0};dist_exact={1,2};
    dist=latt.coor_abs_relat(coor_i,coor_j);
    EXPECT_FALSE( diff(dist, dist_exact, 0.0) );
}

TEST(supercubicTest, inverse)
{
    TensorHao<int,1> n(2); n = {3,4};
    Supercubic latt(n);

    EXPECT_EQ(latt.inverse(0), 0);
    EXPECT_EQ(latt.inverse(1), 2);
    EXPECT_EQ(latt.inverse(2), 1);
    EXPECT_EQ(latt.inverse(3), 9);
    EXPECT_EQ(latt.inverse(4), 11);
    EXPECT_EQ(latt.inverse(5), 10);
    EXPECT_EQ(latt.inverse(6), 6);
    EXPECT_EQ(latt.inverse(7), 8);
    EXPECT_EQ(latt.inverse(8), 7);
    EXPECT_EQ(latt.inverse(9), 3);
    EXPECT_EQ(latt.inverse(10), 5);
    EXPECT_EQ(latt.inverse(11), 4);
}