//
// Created by boruoshihao on 12/20/16.
//
#include <fstream>
#include "../include/supercubic.h"
#include "../../testHao/gtest_custom.h"
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
    MPIBarrier();

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

TEST(supercubicTest, readWriteBcast)
{
    string filename="latt_param.dat";
    TensorHao<int,1> n(3); n = {2,3,4};
    Supercubic latt, lattBase(n);

    if( MPIRank() == 0 ) lattBase.write(filename);
    if( MPIRank() == 0 ) latt.read(filename);
    MPIBcast(latt);
    removeFile(filename);

    EXPECT_FALSE( diff( n, latt.getN(), 0.0 ) );
    EXPECT_EQ( n.size(), latt.getDimen() );
    EXPECT_EQ( static_cast<size_t>(24), latt.getL() );
}

TEST(supercubicTest, getNearestNeighborHopping)
{
    TensorHao<int,1> n(2); n = {3,4};
    Supercubic latt(n);

    TensorHao<double,1> k(2); k={0.01, 0.02};
    double t1 = 1.0;

    TensorHao<size_t, 1> sit_i, sit_j;
    TensorHao<complex<double>, 1> hop;

    tie(sit_i, sit_j, hop) = getNearestNeighborHopping(latt, t1, k);

    size_t Nhop = sit_i.size();
    TensorHao<size_t, 1> sit_i_Exact(Nhop), sit_j_Exact(Nhop);
    TensorHao<complex<double>, 1> hopExact(4);
    sit_i_Exact = {0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7,
                   8, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10, 11, 11, 11, 11};
    sit_j_Exact = {2, 1, 9, 3, 0, 2, 10, 4, 1, 0, 11, 5, 5, 4, 0, 6, 3, 5, 1, 7, 4, 3, 2, 8, 8, 7, 3, 9, 6, 8, 4,
                   10, 7, 6, 5, 11, 11, 10, 6, 0, 9, 11, 7, 1, 10, 9, 8, 2};
    hopExact = { {-0.9997806834748455, 0.02094241988335696}, {-0.9997806834748455, -0.02094241988335696},
                 {-0.9995065603657316, 0.03141075907812829}, {-0.9995065603657316, -0.03141075907812829} };

    EXPECT_FALSE( diff(sit_i, sit_i_Exact, 0.0) );
    EXPECT_FALSE( diff(sit_j, sit_j_Exact, 0.0) );
    for(size_t i = 0; i < Nhop; ++i)
    {
        EXPECT_COMPLEXDOUBLE_EQ( hop(i), hopExact(i%4) );
    }
}

TEST(supercubicTest, getNearestNeighborDispersion)
{
    TensorHao<int, 1> n(2); n = {3, 4};
    Supercubic latt(n);

    TensorHao<double, 1> k(2); k = {0.01, 0.02};
    double t1 = 1.0;

    TensorHao<double, 1> dispersion = getNearestNeighborDispersion(latt, t1, k);
    TensorHao<double, 1> dispersionExact( latt.getL() );
    dispersionExact = {-3.998574487681154, -0.9629591019852031, -1.035505772528031, -1.9367398487934344, 1.0988755369025167,
                       1.0263288663596886, -0.0005482462182277992, 3.0350671394777233, 2.9625204689348954, -2.0623828851059467,
                       0.9732325005900042, 0.9006858300471763};

    EXPECT_FALSE( diff( dispersion, dispersionExact, 1e-12 ) );
}

TEST(supercubicTest, getContinuousDispersion)
{
    TensorHao<int, 1> n(2); n = {3, 4};
    Supercubic latt(n);

    TensorHao<double, 1> k(2); k = {0.01, 0.02};
    double t1 = 1.0;

    TensorHao<double, 1> dispersion = getContinuousDispersion(latt, t1, k);
    TensorHao<double, 1> dispersionExact( latt.getL() );
    dispersionExact = {0.00142560952460168, 4.475646271351777, 4.300186637554638, 2.5675227538078347, 7.041743415635009,
                       6.86628378183787, 9.673637922592183, 14.147858584419357, 13.972398950622217, 2.370130665786049,
                       6.844351327613224, 6.668891693816085};

    EXPECT_FALSE( diff( dispersion, dispersionExact, 1e-12 ) );
}
