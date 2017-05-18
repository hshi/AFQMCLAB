//
// Created by boruoshihao on 5/18/17.
//

#include "../include/SD2IS.h"
#include "../../../../../common/testHao/gtest_custom.h"
#include "../../../../../common/readWriteHao/include/readWriteHao.h"

using namespace std;
using namespace tensor_hao;

TEST(SD2ISTest, voidConstruction)
{
    SD2IS sd2IS;
    EXPECT_COMPLEXDOUBLE_EQ( 0.0, sd2IS.getLogw() );
    EXPECT_FALSE( sd2IS.getWf().data() );
    EXPECT_EQ( static_cast<size_t>(0), sd2IS.getL() );
    EXPECT_EQ( static_cast<size_t>(0), sd2IS.getNup() );
    EXPECT_EQ( static_cast<size_t>(0), sd2IS.getNdn() );
}

TEST(SD2ISTest, LNupNdnConstruction)
{
    size_t L(10), Nup(5), Ndn(3);
    SD2IS sd2IS(L, Nup, Ndn);
    EXPECT_COMPLEXDOUBLE_EQ( 0.0, sd2IS.getLogw() );
    EXPECT_TRUE( sd2IS.getWf().data() );
    EXPECT_EQ( L, sd2IS.getL() );
    EXPECT_EQ( Nup, sd2IS.getNup() );
    EXPECT_EQ( Ndn, sd2IS.getNdn() );
}

TEST(SD2ISTest, copyConstruction)
{
    size_t L(10), Nup(5), Ndn(3);
    TensorHao<complex<double>,2> wf(L, max(Nup, Ndn) );
    randomFill(wf);
    complex<double> logw(2.0, 3.0);

    SD2IS sd2ISBase(L, Nup, Ndn);
    sd2ISBase.logwRef() = logw;
    sd2ISBase.wfRef() = wf;

    SD2IS sd2IS(sd2ISBase);
    EXPECT_COMPLEXDOUBLE_EQ( logw, sd2IS.getLogw() );
    EXPECT_FALSE( diff( wf, sd2IS.getWf(), 1e-12 ) );
    EXPECT_EQ( L, sd2IS.getL() );
    EXPECT_EQ( Nup, sd2IS.getNup() );
    EXPECT_EQ( Ndn, sd2IS.getNdn() );
    EXPECT_FALSE( diff( wf, sd2ISBase.getWf(), 1e-12 ) );
}

TEST(SD2ISTest, moveConstruction)
{
    size_t L(10), Nup(5), Ndn(3);
    TensorHao<complex<double>,2> wf(L, max(Nup, Ndn) );
    randomFill(wf);
    complex<double> logw(2.0, 3.0);

    SD2IS sd2ISBase(L, Nup, Ndn);
    sd2ISBase.logwRef() = logw;
    sd2ISBase.wfRef() = wf;

    SD2IS sd2IS( move(sd2ISBase) );
    EXPECT_COMPLEXDOUBLE_EQ( logw, sd2IS.getLogw() );
    EXPECT_FALSE( diff( wf, sd2IS.getWf(), 1e-12 ) );
    EXPECT_EQ( L, sd2IS.getL() );
    EXPECT_EQ( Nup, sd2IS.getNup() );
    EXPECT_EQ( Ndn, sd2IS.getNdn() );
    EXPECT_FALSE( sd2ISBase.getWf().data() );
}

TEST(SD2ISTest, copyAssignment)
{
    size_t L(10), Nup(5), Ndn(3);
    TensorHao<complex<double>,2> wf(L, max(Nup, Ndn) );
    randomFill(wf);
    complex<double> logw(2.0, 3.0);

    SD2IS sd2ISBase(L, Nup, Ndn);
    sd2ISBase.logwRef() = logw;
    sd2ISBase.wfRef() = wf;

    SD2IS sd2IS; sd2IS = sd2ISBase;
    EXPECT_COMPLEXDOUBLE_EQ( logw, sd2IS.getLogw() );
    EXPECT_FALSE( diff( wf, sd2IS.getWf(), 1e-12 ) );
    EXPECT_EQ( L, sd2IS.getL() );
    EXPECT_EQ( Nup, sd2IS.getNup() );
    EXPECT_EQ( Ndn, sd2IS.getNdn() );
    EXPECT_FALSE( diff( wf, sd2ISBase.getWf(), 1e-12 ) );
}

TEST(SD2ISTest, moveAssignment)
{
    size_t L(10), Nup(5), Ndn(3);
    TensorHao<complex<double>,2> wf(L, max(Nup, Ndn) );
    randomFill(wf);
    complex<double> logw(2.0, 3.0);

    SD2IS sd2ISBase(L, Nup, Ndn);
    sd2ISBase.logwRef() = logw;
    sd2ISBase.wfRef() = wf;

    SD2IS sd2IS; sd2IS = move(sd2ISBase);
    EXPECT_COMPLEXDOUBLE_EQ( logw, sd2IS.getLogw() );
    EXPECT_FALSE( diff( wf, sd2IS.getWf(), 1e-12 ) );
    EXPECT_EQ( L, sd2IS.getL() );
    EXPECT_EQ( Nup, sd2IS.getNup() );
    EXPECT_EQ( Ndn, sd2IS.getNdn() );
    EXPECT_FALSE( sd2ISBase.getWf().data() );
}

TEST(SD2ISTest, readWriteBcast)
{
    size_t L(10), Nup(5), Ndn(3);
    TensorHao<complex<double>,2> wf(L, max(Nup, Ndn) );
    randomFill(wf);
    complex<double> logw(2.0, 3.0);

    SD2IS sd2ISBase(L, Nup, Ndn), sd2IS;
    sd2ISBase.logwRef() = logw;
    sd2ISBase.wfRef() = wf;

    string filename="SD2IS.dat";
    if( MPIRank() == 0 ) sd2ISBase.write(filename);
    if( MPIRank() == 0 ) sd2IS.read(filename);
    MPIBcast(sd2IS);
    removeFile(filename);

    EXPECT_COMPLEXDOUBLE_EQ( logw, sd2IS.getLogw() );
    EXPECT_FALSE( diff( wf, sd2IS.getWf(), 1e-12 ) );
    EXPECT_EQ( L, sd2IS.getL() );
    EXPECT_EQ( Nup, sd2IS.getNup() );
    EXPECT_EQ( Ndn, sd2IS.getNdn() );
}

#ifdef MPI_HAO
TEST(SD2ISTest, packUnpack)
{
    size_t L(10), Nup(5), Ndn(3);
    TensorHao<complex<double>,2> wf(L, max(Nup, Ndn) );
    randomFill(wf);
    complex<double> logw(2.0, 3.0);

    SD2IS sd2ISBase(L, Nup, Ndn);
    sd2ISBase.logwRef() = logw;
    sd2ISBase.wfRef() = wf;

    SD2IS sd2IS; sd2IS.resize(L, Nup, Ndn);

    int Nbuf = sd2ISBase.returnNbuf();
    vector<char> buf(Nbuf);
    int posit(0); sd2ISBase.pack(buf, posit);
    posit = 0; sd2IS.unpack(buf, posit);

    EXPECT_COMPLEXDOUBLE_EQ( logw, sd2IS.getLogw() );
    EXPECT_FALSE( diff( wf, sd2IS.getWf(), 1e-12 ) );
    EXPECT_EQ( L, sd2IS.getL() );
    EXPECT_EQ( Nup, sd2IS.getNup() );
    EXPECT_EQ( Ndn, sd2IS.getNdn() );
}
#endif
