//
// Created by boruoshihao on 1/11/17.
//

#include "../include/HubbardRealSpaceSOC.h"
#include "../../../../common/testHao/gtest_custom.h"
#include "../../../../common/readWriteHao/include/readWriteHao.h"

using namespace std;
using namespace tensor_hao;

TEST(HubbardRealSpaceSOCTest, voidConstruction)
{
    HubbardRealSpaceSOC hubbard;
    size_t L(0),N(0);
    EXPECT_EQ( L, hubbard.getL() );
    EXPECT_EQ( N, hubbard.getN() );
}

void createInputFile(const string &filename)
{
    size_t L(10), N(5);
    TensorHao< complex<double>, 2 > K(L,L);
    TensorHao< double, 1> mu(L), hx(L), hy(L), hz(L), U(L);
    randomFill(K); randomFill(mu); randomFill(hx);
    randomFill(hy); randomFill(hz); randomFill(U);

    ofstream file;
    file.open(filename, ios::out|ios::trunc);
    if ( ! file.is_open() ) {cout << "Error opening file in File!!! "<<filename<<endl; exit(1);}
    file<<setprecision(16)<<scientific;
    writeFile(L,file);
    writeFile(N,file);
    writeFile( L*L, K.data(), file );
    writeFile( L, mu.data(), file );
    writeFile( L, hx.data(), file );
    writeFile( L, hy.data(), file );
    writeFile( L, hz.data(), file );
    writeFile( L, U.data(), file );
    file.close();
}

TEST(HubbardRealSpaceSOCTest, readWriteBcast)
{
    string filename = "hubbard.dat";

    if( MPIRank() == 0 ) createInputFile(filename);
    MPIBarrier();

    HubbardRealSpaceSOC hubbardOne(filename);
//    if( MPIRank() == 0 ) hubbardOne.write(filename);
//    MPIBarrier();

//    HubbardRealSpaceSOC hubbardTwo;
//    if( MPIRank() == 0 ) hubbardTwo.read(filename);
//    MPIBcast( hubbardTwo );
//
//    EXPECT_EQ( hubbardOne.getL(), hubbardTwo.getL() );
//    EXPECT_EQ( hubbardOne.getN(), hubbardTwo.getN() );
//    EXPECT_FALSE( diff(hubbardOne.getK(),  hubbardTwo.getK(),  1e-12) );
//    EXPECT_FALSE( diff(hubbardOne.getMu(), hubbardTwo.getMu(), 1e-12) );
//    EXPECT_FALSE( diff(hubbardOne.getHx(), hubbardTwo.getHx(), 1e-12) );
//    EXPECT_FALSE( diff(hubbardOne.getHy(), hubbardTwo.getHy(), 1e-12) );
//    EXPECT_FALSE( diff(hubbardOne.getHz(), hubbardTwo.getHz(), 1e-12) );
//    EXPECT_FALSE( diff(hubbardOne.getU(),  hubbardTwo.getU(),  1e-12) );

    removeFile(filename);
}