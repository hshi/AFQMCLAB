//
// Created by boruoshihao on 5/17/17.
//

#include "../include/SD2s.h"
#include "../../../../../common/testHao/gtest_custom.h"
#include "../../../../../common/readWriteHao/include/readWriteHao.h"

using namespace std;
using namespace tensor_hao;

TEST(SD2sTest, voidConstruction)
{
    SD2s sd2s;
    EXPECT_COMPLEXDOUBLE_EQ( 0.0, sd2s.getLogw() );
    EXPECT_FALSE( sd2s.getWfUp().data() );
    EXPECT_FALSE( sd2s.getWfDn().data() );
    EXPECT_EQ( static_cast<size_t>(0), sd2s.getL() );
    EXPECT_EQ( static_cast<size_t>(0), sd2s.getNup() );
    EXPECT_EQ( static_cast<size_t>(0), sd2s.getNdn() );
}

TEST(SD2sTest, LNupNdnConstruction)
{
    size_t L(10), Nup(5), Ndn(3);
    SD2s sd2s(L, Nup, Ndn);
    EXPECT_COMPLEXDOUBLE_EQ( 0.0, sd2s.getLogw() );
    EXPECT_TRUE( sd2s.getWfUp().data() );
    EXPECT_TRUE( sd2s.getWfDn().data() );
    EXPECT_EQ( L, sd2s.getL() );
    EXPECT_EQ( Nup, sd2s.getNup() );
    EXPECT_EQ( Ndn, sd2s.getNdn() );
}

TEST(SD2sTest, copyConstruction)
{
    size_t L(10), Nup(5), Ndn(3);
    TensorHao<complex<double>,2> wfUp(L,Nup), wfDn(L, Ndn);
    randomFill(wfUp); randomFill(wfDn);
    complex<double> logw(2.0, 3.0);

    SD2s sd2sBase;
    sd2sBase.logwRef() = logw;
    sd2sBase.wfUpRef() = wfUp;
    sd2sBase.wfDnRef() = wfDn;

    SD2s sd2s(sd2sBase);
    EXPECT_COMPLEXDOUBLE_EQ( logw, sd2s.getLogw() );
    EXPECT_FALSE( diff( wfUp, sd2s.getWfUp(), 1e-12 ) );
    EXPECT_FALSE( diff( wfDn, sd2s.getWfDn(), 1e-12 ) );
    EXPECT_EQ( L, sd2s.getL() );
    EXPECT_EQ( Nup, sd2s.getNup() );
    EXPECT_EQ( Ndn, sd2s.getNdn() );
    EXPECT_FALSE( diff( wfUp, sd2sBase.getWfUp(), 1e-12 ) );
    EXPECT_FALSE( diff( wfDn, sd2sBase.getWfDn(), 1e-12 ) );
}

TEST(SD2sTest, moveConstruction)
{
    size_t L(10), Nup(5), Ndn(3);
    TensorHao<complex<double>,2> wfUp(L,Nup), wfDn(L, Ndn);
    randomFill(wfUp); randomFill(wfDn);
    complex<double> logw(2.0, 3.0);

    SD2s sd2sBase;
    sd2sBase.logwRef() = logw;
    sd2sBase.wfUpRef() = wfUp;
    sd2sBase.wfDnRef() = wfDn;

    SD2s sd2s( move(sd2sBase) );
    EXPECT_COMPLEXDOUBLE_EQ( logw, sd2s.getLogw() );
    EXPECT_FALSE( diff( wfUp, sd2s.getWfUp(), 1e-12 ) );
    EXPECT_FALSE( diff( wfDn, sd2s.getWfDn(), 1e-12 ) );
    EXPECT_EQ( L, sd2s.getL() );
    EXPECT_EQ( Nup, sd2s.getNup() );
    EXPECT_EQ( Ndn, sd2s.getNdn() );
    EXPECT_FALSE( sd2sBase.getWfUp().data() );
    EXPECT_FALSE( sd2sBase.getWfDn().data() );
}

TEST(SD2sTest, copyAssignment)
{
    size_t L(10), Nup(5), Ndn(3);
    TensorHao<complex<double>,2> wfUp(L,Nup), wfDn(L, Ndn);
    randomFill(wfUp); randomFill(wfDn);
    complex<double> logw(2.0, 3.0);

    SD2s sd2sBase;
    sd2sBase.logwRef() = logw;
    sd2sBase.wfUpRef() = wfUp;
    sd2sBase.wfDnRef() = wfDn;

    SD2s sd2s; sd2s=sd2sBase;
    EXPECT_COMPLEXDOUBLE_EQ( logw, sd2s.getLogw() );
    EXPECT_FALSE( diff( wfUp, sd2s.getWfUp(), 1e-12 ) );
    EXPECT_FALSE( diff( wfDn, sd2s.getWfDn(), 1e-12 ) );
    EXPECT_EQ( L, sd2s.getL() );
    EXPECT_EQ( Nup, sd2s.getNup() );
    EXPECT_EQ( Ndn, sd2s.getNdn() );
    EXPECT_FALSE( diff( wfUp, sd2sBase.getWfUp(), 1e-12 ) );
    EXPECT_FALSE( diff( wfDn, sd2sBase.getWfDn(), 1e-12 ) );
}

TEST(SD2sTest, moveAssignment)
{
    size_t L(10), Nup(5), Ndn(3);
    TensorHao<complex<double>,2> wfUp(L,Nup), wfDn(L, Ndn);
    randomFill(wfUp); randomFill(wfDn);
    complex<double> logw(2.0, 3.0);

    SD2s sd2sBase;
    sd2sBase.logwRef() = logw;
    sd2sBase.wfUpRef() = wfUp;
    sd2sBase.wfDnRef() = wfDn;

    SD2s sd2s; sd2s=move(sd2sBase);
    EXPECT_COMPLEXDOUBLE_EQ( logw, sd2s.getLogw() );
    EXPECT_FALSE( diff( wfUp, sd2s.getWfUp(), 1e-12 ) );
    EXPECT_FALSE( diff( wfDn, sd2s.getWfDn(), 1e-12 ) );
    EXPECT_EQ( L, sd2s.getL() );
    EXPECT_EQ( Nup, sd2s.getNup() );
    EXPECT_EQ( Ndn, sd2s.getNdn() );
    EXPECT_FALSE( sd2sBase.getWfUp().data() );
    EXPECT_FALSE( sd2sBase.getWfDn().data() );
}

TEST(SD2sTest, readWriteBcast)
{
    size_t L(10), Nup(5), Ndn(3);
    TensorHao<complex<double>,2> wfUp(L,Nup), wfDn(L, Ndn);
    randomFill(wfUp); randomFill(wfDn);
    complex<double> logw(2.0, 3.0);

    SD2s sd2sBase, sd2s;
    sd2sBase.logwRef() = logw;
    sd2sBase.wfUpRef() = wfUp;
    sd2sBase.wfDnRef() = wfDn;

    string filename="SD2s.dat";
    if( MPIRank() == 0 ) sd2sBase.write(filename);
    if( MPIRank() == 0 ) sd2s.read(filename);
    MPIBcast(sd2s);
    removeFile(filename);

    EXPECT_COMPLEXDOUBLE_EQ( logw, sd2s.getLogw() );
    EXPECT_FALSE( diff( wfUp, sd2s.getWfUp(), 1e-12 ) );
    EXPECT_FALSE( diff( wfDn, sd2s.getWfDn(), 1e-12 ) );
    EXPECT_EQ( L, sd2s.getL() );
    EXPECT_EQ( Nup, sd2s.getNup() );
    EXPECT_EQ( Ndn, sd2s.getNdn() );
}

#ifdef MPI_HAO
TEST(SD2sTest, packUnpack)
{
    size_t L(10), Nup(5), Ndn(3);
    TensorHao<complex<double>,2> wfUp(L,Nup), wfDn(L, Ndn);
    randomFill(wfUp); randomFill(wfDn);
    complex<double> logw(2.0, 3.0);

    SD2s sd2sBase;
    sd2sBase.logwRef() = logw;
    sd2sBase.wfUpRef() = wfUp;
    sd2sBase.wfDnRef() = wfDn;

    SD2s sd2s;
    sd2s.resize(L, Nup, Ndn);

    int Nbuf = sd2sBase.returnNbuf();
    vector<char> buf(Nbuf);
    int posit(0); sd2sBase.pack(buf, posit);
    posit = 0; sd2s.unpack(buf, posit);

    EXPECT_COMPLEXDOUBLE_EQ( logw, sd2s.getLogw() );
    EXPECT_FALSE( diff( wfUp, sd2s.getWfUp(), 1e-12 ) );
    EXPECT_FALSE( diff( wfDn, sd2s.getWfDn(), 1e-12 ) );
    EXPECT_EQ( L, sd2s.getL() );
    EXPECT_EQ( Nup, sd2s.getNup() );
    EXPECT_EQ( Ndn, sd2s.getNdn() );
}
#endif

TEST(SD2sTest, normalize)
{
    size_t L(4), Nup(3), Ndn=2;
    SD2s sd2s(L,Nup, Ndn);
    sd2s.wfUpRef() = {{1.0,1.0}, {2.0,1.0}, {3.0,1.0}, {4.0,1.0},
                     {2.0,2.0}, {3.0,1.0}, {5.0,2.0}, {6.0,1.0},
                     {4.0,1.0}, {3.0,3.0}, {2.0,2.0}, {2.0,6.0} };

    sd2s.wfDnRef() = {{1.0,2.0}, {2.0,3.0}, {3.0,4.0}, {4.0,5.0},
                      {2.0,2.0}, {3.0,3.0}, {5.0,2.0}, {6.0,3.0} };

    complex<double> logw; double ratio;
    logw = sd2s.normalize(ratio);

    complex<double> logwExact(5.83560522196797, 0.0);
    double ratioExact(0.14186161056920224);
    EXPECT_COMPLEXDOUBLE_EQ(logw, logwExact);
    EXPECT_DOUBLE_EQ(ratio, ratioExact);
}