//
// Created by boruoshihao on 5/17/17.
//

#include "../include/SD2Spin.h"
#include "../../../../../common/testHao/gtest_custom.h"
#include "../../../../../common/readWriteHao/include/readWriteHao.h"

using namespace std;
using namespace tensor_hao;

TEST(SD2SpinTest, voidConstruction)
{
    SD2Spin sd2Spin;
    EXPECT_COMPLEXDOUBLE_EQ( 0.0, sd2Spin.getLogw() );
    EXPECT_FALSE( sd2Spin.getWfUp().data() );
    EXPECT_FALSE( sd2Spin.getWfDn().data() );
    EXPECT_EQ( static_cast<size_t>(0), sd2Spin.getL() );
    EXPECT_EQ( static_cast<size_t>(0), sd2Spin.getNup() );
    EXPECT_EQ( static_cast<size_t>(0), sd2Spin.getNdn() );
}

TEST(SD2SpinTest, LNupNdnConstruction)
{
    size_t L(10), Nup(5), Ndn(3);
    SD2Spin sd2Spin(L, Nup, Ndn);
    EXPECT_COMPLEXDOUBLE_EQ( 0.0, sd2Spin.getLogw() );
    EXPECT_TRUE( sd2Spin.getWfUp().data() );
    EXPECT_TRUE( sd2Spin.getWfDn().data() );
    EXPECT_EQ( L, sd2Spin.getL() );
    EXPECT_EQ( Nup, sd2Spin.getNup() );
    EXPECT_EQ( Ndn, sd2Spin.getNdn() );
}

TEST(SD2SpinTest, copyConstruction)
{
    size_t L(10), Nup(5), Ndn(3);
    TensorHao<complex<double>,2> wfUp(L,Nup), wfDn(L, Ndn);
    randomFill(wfUp); randomFill(wfDn);
    complex<double> logw(2.0, 3.0);

    SD2Spin sd2SpinBase;
    sd2SpinBase.logwRef() = logw;
    sd2SpinBase.wfUpRef() = wfUp;
    sd2SpinBase.wfDnRef() = wfDn;

    SD2Spin sd2Spin(sd2SpinBase);
    EXPECT_COMPLEXDOUBLE_EQ( logw, sd2Spin.getLogw() );
    EXPECT_FALSE( diff( wfUp, sd2Spin.getWfUp(), 1e-12 ) );
    EXPECT_FALSE( diff( wfDn, sd2Spin.getWfDn(), 1e-12 ) );
    EXPECT_EQ( L, sd2Spin.getL() );
    EXPECT_EQ( Nup, sd2Spin.getNup() );
    EXPECT_EQ( Ndn, sd2Spin.getNdn() );
    EXPECT_FALSE( diff( wfUp, sd2SpinBase.getWfUp(), 1e-12 ) );
    EXPECT_FALSE( diff( wfDn, sd2SpinBase.getWfDn(), 1e-12 ) );
}

TEST(SD2SpinTest, moveConstruction)
{
    size_t L(10), Nup(5), Ndn(3);
    TensorHao<complex<double>,2> wfUp(L,Nup), wfDn(L, Ndn);
    randomFill(wfUp); randomFill(wfDn);
    complex<double> logw(2.0, 3.0);

    SD2Spin sd2SpinBase;
    sd2SpinBase.logwRef() = logw;
    sd2SpinBase.wfUpRef() = wfUp;
    sd2SpinBase.wfDnRef() = wfDn;

    SD2Spin sd2Spin( move(sd2SpinBase) );
    EXPECT_COMPLEXDOUBLE_EQ( logw, sd2Spin.getLogw() );
    EXPECT_FALSE( diff( wfUp, sd2Spin.getWfUp(), 1e-12 ) );
    EXPECT_FALSE( diff( wfDn, sd2Spin.getWfDn(), 1e-12 ) );
    EXPECT_EQ( L, sd2Spin.getL() );
    EXPECT_EQ( Nup, sd2Spin.getNup() );
    EXPECT_EQ( Ndn, sd2Spin.getNdn() );
    EXPECT_FALSE( sd2SpinBase.getWfUp().data() );
    EXPECT_FALSE( sd2SpinBase.getWfDn().data() );
}

TEST(SD2SpinTest, copyAssignment)
{
    size_t L(10), Nup(5), Ndn(3);
    TensorHao<complex<double>,2> wfUp(L,Nup), wfDn(L, Ndn);
    randomFill(wfUp); randomFill(wfDn);
    complex<double> logw(2.0, 3.0);

    SD2Spin sd2SpinBase;
    sd2SpinBase.logwRef() = logw;
    sd2SpinBase.wfUpRef() = wfUp;
    sd2SpinBase.wfDnRef() = wfDn;

    SD2Spin sd2Spin; sd2Spin=sd2SpinBase;
    EXPECT_COMPLEXDOUBLE_EQ( logw, sd2Spin.getLogw() );
    EXPECT_FALSE( diff( wfUp, sd2Spin.getWfUp(), 1e-12 ) );
    EXPECT_FALSE( diff( wfDn, sd2Spin.getWfDn(), 1e-12 ) );
    EXPECT_EQ( L, sd2Spin.getL() );
    EXPECT_EQ( Nup, sd2Spin.getNup() );
    EXPECT_EQ( Ndn, sd2Spin.getNdn() );
    EXPECT_FALSE( diff( wfUp, sd2SpinBase.getWfUp(), 1e-12 ) );
    EXPECT_FALSE( diff( wfDn, sd2SpinBase.getWfDn(), 1e-12 ) );
}

TEST(SD2SpinTest, moveAssignment)
{
    size_t L(10), Nup(5), Ndn(3);
    TensorHao<complex<double>,2> wfUp(L,Nup), wfDn(L, Ndn);
    randomFill(wfUp); randomFill(wfDn);
    complex<double> logw(2.0, 3.0);

    SD2Spin sd2SpinBase;
    sd2SpinBase.logwRef() = logw;
    sd2SpinBase.wfUpRef() = wfUp;
    sd2SpinBase.wfDnRef() = wfDn;

    SD2Spin sd2Spin; sd2Spin=move(sd2SpinBase);
    EXPECT_COMPLEXDOUBLE_EQ( logw, sd2Spin.getLogw() );
    EXPECT_FALSE( diff( wfUp, sd2Spin.getWfUp(), 1e-12 ) );
    EXPECT_FALSE( diff( wfDn, sd2Spin.getWfDn(), 1e-12 ) );
    EXPECT_EQ( L, sd2Spin.getL() );
    EXPECT_EQ( Nup, sd2Spin.getNup() );
    EXPECT_EQ( Ndn, sd2Spin.getNdn() );
    EXPECT_FALSE( sd2SpinBase.getWfUp().data() );
    EXPECT_FALSE( sd2SpinBase.getWfDn().data() );
}

TEST(SDTest, readWriteBcast)
{
    size_t L(10), Nup(5), Ndn(3);
    TensorHao<complex<double>,2> wfUp(L,Nup), wfDn(L, Ndn);
    randomFill(wfUp); randomFill(wfDn);
    complex<double> logw(2.0, 3.0);

    SD2Spin sd2SpinBase, sd2Spin;
    sd2SpinBase.logwRef() = logw;
    sd2SpinBase.wfUpRef() = wfUp;
    sd2SpinBase.wfDnRef() = wfDn;

    string filename="SD2Spin.dat";
    if( MPIRank() == 0 ) sd2SpinBase.write(filename);
    if( MPIRank() == 0 ) sd2Spin.read(filename);
    MPIBcast(sd2Spin);
    removeFile(filename);

    EXPECT_COMPLEXDOUBLE_EQ( logw, sd2Spin.getLogw() );
    EXPECT_FALSE( diff( wfUp, sd2Spin.getWfUp(), 1e-12 ) );
    EXPECT_FALSE( diff( wfDn, sd2Spin.getWfDn(), 1e-12 ) );
    EXPECT_EQ( L, sd2Spin.getL() );
    EXPECT_EQ( Nup, sd2Spin.getNup() );
    EXPECT_EQ( Ndn, sd2Spin.getNdn() );
}

#ifdef MPI_HAO
TEST(SDTest, packUnpack)
{
    size_t L(10), Nup(5), Ndn(3);
    TensorHao<complex<double>,2> wfUp(L,Nup), wfDn(L, Ndn);
    randomFill(wfUp); randomFill(wfDn);
    complex<double> logw(2.0, 3.0);

    SD2Spin sd2SpinBase;
    sd2SpinBase.logwRef() = logw;
    sd2SpinBase.wfUpRef() = wfUp;
    sd2SpinBase.wfDnRef() = wfDn;

    SD2Spin sd2Spin;
    sd2Spin.resize(L, Nup, Ndn);

    int Nbuf = sd2SpinBase.returnNbuf();
    vector<char> buf(Nbuf);
    int posit(0); sd2SpinBase.pack(buf, posit);
    posit = 0; sd2Spin.unpack(buf, posit);

    EXPECT_COMPLEXDOUBLE_EQ( logw, sd2Spin.getLogw() );
    EXPECT_FALSE( diff( wfUp, sd2Spin.getWfUp(), 1e-12 ) );
    EXPECT_FALSE( diff( wfDn, sd2Spin.getWfDn(), 1e-12 ) );
    EXPECT_EQ( L, sd2Spin.getL() );
    EXPECT_EQ( Nup, sd2Spin.getNup() );
    EXPECT_EQ( Ndn, sd2Spin.getNdn() );
}
#endif