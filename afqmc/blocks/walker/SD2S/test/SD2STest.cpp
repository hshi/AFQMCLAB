//
// Created by boruoshihao on 5/17/17.
//

#include "../include/SD2S.h"
#include "../../../../../common/testHao/gtest_custom.h"
#include "../../../../../common/readWriteHao/include/readWriteHao.h"

using namespace std;
using namespace tensor_hao;

TEST(SD2STest, voidConstruction)
{
    SD2S sd2S;
    EXPECT_COMPLEXDOUBLE_EQ( 0.0, sd2S.getLogw() );
    EXPECT_FALSE( sd2S.getWfUp().data() );
    EXPECT_FALSE( sd2S.getWfDn().data() );
    EXPECT_EQ( static_cast<size_t>(0), sd2S.getL() );
    EXPECT_EQ( static_cast<size_t>(0), sd2S.getNup() );
    EXPECT_EQ( static_cast<size_t>(0), sd2S.getNdn() );
}

TEST(SD2STest, LNupNdnConstruction)
{
    size_t L(10), Nup(5), Ndn(3);
    SD2S sd2S(L, Nup, Ndn);
    EXPECT_COMPLEXDOUBLE_EQ( 0.0, sd2S.getLogw() );
    EXPECT_TRUE( sd2S.getWfUp().data() );
    EXPECT_TRUE( sd2S.getWfDn().data() );
    EXPECT_EQ( L, sd2S.getL() );
    EXPECT_EQ( Nup, sd2S.getNup() );
    EXPECT_EQ( Ndn, sd2S.getNdn() );
}

TEST(SD2STest, copyConstruction)
{
    size_t L(10), Nup(5), Ndn(3);
    TensorHao<complex<double>,2> wfUp(L,Nup), wfDn(L, Ndn);
    randomFill(wfUp); randomFill(wfDn);
    complex<double> logw(2.0, 3.0);

    SD2S sd2SBase;
    sd2SBase.logwRef() = logw;
    sd2SBase.wfUpRef() = wfUp;
    sd2SBase.wfDnRef() = wfDn;

    SD2S sd2S(sd2SBase);
    EXPECT_COMPLEXDOUBLE_EQ( logw, sd2S.getLogw() );
    EXPECT_FALSE( diff( wfUp, sd2S.getWfUp(), 1e-12 ) );
    EXPECT_FALSE( diff( wfDn, sd2S.getWfDn(), 1e-12 ) );
    EXPECT_EQ( L, sd2S.getL() );
    EXPECT_EQ( Nup, sd2S.getNup() );
    EXPECT_EQ( Ndn, sd2S.getNdn() );
    EXPECT_FALSE( diff( wfUp, sd2SBase.getWfUp(), 1e-12 ) );
    EXPECT_FALSE( diff( wfDn, sd2SBase.getWfDn(), 1e-12 ) );
}

TEST(SD2STest, moveConstruction)
{
    size_t L(10), Nup(5), Ndn(3);
    TensorHao<complex<double>,2> wfUp(L,Nup), wfDn(L, Ndn);
    randomFill(wfUp); randomFill(wfDn);
    complex<double> logw(2.0, 3.0);

    SD2S sd2SBase;
    sd2SBase.logwRef() = logw;
    sd2SBase.wfUpRef() = wfUp;
    sd2SBase.wfDnRef() = wfDn;

    SD2S sd2S( move(sd2SBase) );
    EXPECT_COMPLEXDOUBLE_EQ( logw, sd2S.getLogw() );
    EXPECT_FALSE( diff( wfUp, sd2S.getWfUp(), 1e-12 ) );
    EXPECT_FALSE( diff( wfDn, sd2S.getWfDn(), 1e-12 ) );
    EXPECT_EQ( L, sd2S.getL() );
    EXPECT_EQ( Nup, sd2S.getNup() );
    EXPECT_EQ( Ndn, sd2S.getNdn() );
    EXPECT_FALSE( sd2SBase.getWfUp().data() );
    EXPECT_FALSE( sd2SBase.getWfDn().data() );
}

TEST(SD2STest, copyAssignment)
{
    size_t L(10), Nup(5), Ndn(3);
    TensorHao<complex<double>,2> wfUp(L,Nup), wfDn(L, Ndn);
    randomFill(wfUp); randomFill(wfDn);
    complex<double> logw(2.0, 3.0);

    SD2S sd2SBase;
    sd2SBase.logwRef() = logw;
    sd2SBase.wfUpRef() = wfUp;
    sd2SBase.wfDnRef() = wfDn;

    SD2S sd2S; sd2S=sd2SBase;
    EXPECT_COMPLEXDOUBLE_EQ( logw, sd2S.getLogw() );
    EXPECT_FALSE( diff( wfUp, sd2S.getWfUp(), 1e-12 ) );
    EXPECT_FALSE( diff( wfDn, sd2S.getWfDn(), 1e-12 ) );
    EXPECT_EQ( L, sd2S.getL() );
    EXPECT_EQ( Nup, sd2S.getNup() );
    EXPECT_EQ( Ndn, sd2S.getNdn() );
    EXPECT_FALSE( diff( wfUp, sd2SBase.getWfUp(), 1e-12 ) );
    EXPECT_FALSE( diff( wfDn, sd2SBase.getWfDn(), 1e-12 ) );
}

TEST(SD2STest, moveAssignment)
{
    size_t L(10), Nup(5), Ndn(3);
    TensorHao<complex<double>,2> wfUp(L,Nup), wfDn(L, Ndn);
    randomFill(wfUp); randomFill(wfDn);
    complex<double> logw(2.0, 3.0);

    SD2S sd2SBase;
    sd2SBase.logwRef() = logw;
    sd2SBase.wfUpRef() = wfUp;
    sd2SBase.wfDnRef() = wfDn;

    SD2S sd2S; sd2S=move(sd2SBase);
    EXPECT_COMPLEXDOUBLE_EQ( logw, sd2S.getLogw() );
    EXPECT_FALSE( diff( wfUp, sd2S.getWfUp(), 1e-12 ) );
    EXPECT_FALSE( diff( wfDn, sd2S.getWfDn(), 1e-12 ) );
    EXPECT_EQ( L, sd2S.getL() );
    EXPECT_EQ( Nup, sd2S.getNup() );
    EXPECT_EQ( Ndn, sd2S.getNdn() );
    EXPECT_FALSE( sd2SBase.getWfUp().data() );
    EXPECT_FALSE( sd2SBase.getWfDn().data() );
}

TEST(SD2STest, readWriteBcast)
{
    size_t L(10), Nup(5), Ndn(3);
    TensorHao<complex<double>,2> wfUp(L,Nup), wfDn(L, Ndn);
    randomFill(wfUp); randomFill(wfDn);
    complex<double> logw(2.0, 3.0);

    SD2S sd2SBase, sd2S;
    sd2SBase.logwRef() = logw;
    sd2SBase.wfUpRef() = wfUp;
    sd2SBase.wfDnRef() = wfDn;

    string filename="SD2S.dat";
    if( MPIRank() == 0 ) sd2SBase.write(filename);
    if( MPIRank() == 0 ) sd2S.read(filename);
    MPIBcast(sd2S);
    removeFile(filename);

    EXPECT_COMPLEXDOUBLE_EQ( logw, sd2S.getLogw() );
    EXPECT_FALSE( diff( wfUp, sd2S.getWfUp(), 1e-12 ) );
    EXPECT_FALSE( diff( wfDn, sd2S.getWfDn(), 1e-12 ) );
    EXPECT_EQ( L, sd2S.getL() );
    EXPECT_EQ( Nup, sd2S.getNup() );
    EXPECT_EQ( Ndn, sd2S.getNdn() );
}

#ifdef MPI_HAO
TEST(SD2STest, packUnpack)
{
    size_t L(10), Nup(5), Ndn(3);
    TensorHao<complex<double>,2> wfUp(L,Nup), wfDn(L, Ndn);
    randomFill(wfUp); randomFill(wfDn);
    complex<double> logw(2.0, 3.0);

    SD2S sd2SBase;
    sd2SBase.logwRef() = logw;
    sd2SBase.wfUpRef() = wfUp;
    sd2SBase.wfDnRef() = wfDn;

    SD2S sd2S;
    sd2S.resize(L, Nup, Ndn);

    int Nbuf = sd2SBase.returnNbuf();
    vector<char> buf(Nbuf);
    int posit(0); sd2SBase.pack(buf, posit);
    posit = 0; sd2S.unpack(buf, posit);

    EXPECT_COMPLEXDOUBLE_EQ( logw, sd2S.getLogw() );
    EXPECT_FALSE( diff( wfUp, sd2S.getWfUp(), 1e-12 ) );
    EXPECT_FALSE( diff( wfDn, sd2S.getWfDn(), 1e-12 ) );
    EXPECT_EQ( L, sd2S.getL() );
    EXPECT_EQ( Nup, sd2S.getNup() );
    EXPECT_EQ( Ndn, sd2S.getNdn() );
}
#endif
