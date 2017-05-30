//
// Created by boruoshihao on 1/11/17.
//

#include "../include/HubbardSOC.h"
#include "../../../../common/testHao/gtest_custom.h"
#include "../../../../common/readWriteHao/include/readWriteHao.h"
#include "../../../blocks/oneBodyWalkerOperation/hopSDOperation/include/hopSDOperation.h"

using namespace std;
using namespace tensor_hao;

TEST(HubbardRealSpaceSOCTest, voidConstruction)
{
    HubbardSOC hubbard;
    size_t L(0),N(0);
    EXPECT_EQ( L, hubbard.getL() );
    EXPECT_EQ( N, hubbard.getN() );
    EXPECT_FALSE( hubbard.getKEigenStatus() );
}

void createInputFile(const string &filename)
{
    size_t L(10), N(5);
    TensorHao< complex<double>, 2 > K(2*L,2*L);
    TensorHao< double, 1> mu(L), hx(L), hy(L), hz(L), U(L);
    randomFill(K);  K+=conjtrans(K);
    randomFill(mu); randomFill(hx);
    randomFill(hy); randomFill(hz); randomFill(U);

    ofstream file;
    file.open(filename, ios::out|ios::trunc);
    if ( ! file.is_open() ) {cout << "Error opening file in File!!! "<<filename<<endl; exit(1);}
    file<<setprecision(16)<<scientific;
    writeFile(L,file);
    writeFile(N,file);
    writeFile( 4*L*L, K.data(), file );
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

    HubbardSOC hubbardOne(filename);
    MPIBarrier();

    if( MPIRank() == 0 ) hubbardOne.write(filename);
    MPIBarrier();

    HubbardSOC hubbardTwo;
    if( MPIRank() == 0 ) hubbardTwo.read(filename);
    MPIBcast( hubbardTwo );

    EXPECT_EQ( hubbardOne.getL(), hubbardTwo.getL() );
    EXPECT_EQ( hubbardOne.getN(), hubbardTwo.getN() );
    EXPECT_FALSE( diff(hubbardOne.getK(),  hubbardTwo.getK(),  1e-12) );
    EXPECT_FALSE( diff(hubbardOne.getMu(), hubbardTwo.getMu(), 1e-12) );
    EXPECT_FALSE( diff(hubbardOne.getHx(), hubbardTwo.getHx(), 1e-12) );
    EXPECT_FALSE( diff(hubbardOne.getHy(), hubbardTwo.getHy(), 1e-12) );
    EXPECT_FALSE( diff(hubbardOne.getHz(), hubbardTwo.getHz(), 1e-12) );
    EXPECT_FALSE( diff(hubbardOne.getU(),  hubbardTwo.getU(),  1e-12) );
    EXPECT_FALSE( hubbardTwo.getKEigenStatus() );
    EXPECT_FALSE( hubbardTwo.getKEigenValue().data() );
    EXPECT_FALSE( hubbardTwo.getKEigenVector().data() );

    removeFile(filename);
}

TEST(HubbardRealSpaceSOCTest, returnExpAlphaK)
{
    string filename = "hubbard.dat";

    if( MPIRank() == 0 ) createInputFile(filename);
    MPIBarrier();

    double dt = 1; size_t projectSize=100;
    HubbardSOC hubbard(filename);
    Hop expMinusDtK = hubbard.returnExpMinusAlphaK(dt);
    SD walker( 2*hubbard.getL(), hubbard.getN() );
    SD walkerNew( 2*hubbard.getL(), hubbard.getN() );
    walker.randomFill();

    HopSDOperation oneBodyWalkerRightOperation;
    for(size_t i = 0; i < projectSize; ++i)
    {
        oneBodyWalkerRightOperation.applyToRight(expMinusDtK, walker, walkerNew);
        walker = move( walkerNew );
        walker.normalize();
    }

    const complex<double> *walkerPointer      = walker.getWf().data();
    const complex<double> *walkerPointerExact = hubbard.getKEigenVector().data();

    for(size_t i = 0; i < 2*hubbard.getL()*hubbard.getN() ; ++i)
    {
        EXPECT_NEAR(abs( walkerPointer[i]), abs(walkerPointerExact[i]), 1e-12 );
    }

    removeFile(filename);
}