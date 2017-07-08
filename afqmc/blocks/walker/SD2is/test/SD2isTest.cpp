//
// Created by boruoshihao on 5/18/17.
//

#include "../include/SD2is.h"
#include "../../../../../common/testHao/gtest_custom.h"
#include "../../../../../common/readWriteHao/include/readWriteHao.h"

using namespace std;
using namespace tensor_hao;

TEST(SD2isTest, voidConstruction)
{
    SD2is sd2is;
    EXPECT_COMPLEXDOUBLE_EQ( 0.0, sd2is.getLogw() );
    EXPECT_FALSE( sd2is.getWf().data() );
    EXPECT_EQ( static_cast<size_t>(0), sd2is.getL() );
    EXPECT_EQ( static_cast<size_t>(0), sd2is.getNup() );
    EXPECT_EQ( static_cast<size_t>(0), sd2is.getNdn() );
}

TEST(SD2isTest, LNupNdnConstruction)
{
    size_t L(10), Nup(5), Ndn(3);
    SD2is sd2is(L, Nup, Ndn);
    EXPECT_COMPLEXDOUBLE_EQ( 0.0, sd2is.getLogw() );
    EXPECT_TRUE( sd2is.getWf().data() );
    EXPECT_EQ( L, sd2is.getL() );
    EXPECT_EQ( Nup, sd2is.getNup() );
    EXPECT_EQ( Ndn, sd2is.getNdn() );
}

TEST(SD2isTest, copyConstruction)
{
    size_t L(10), Nup(5), Ndn(3);
    TensorHao<complex<double>,2> wf(L, max(Nup, Ndn) );
    randomFill(wf);
    complex<double> logw(2.0, 3.0);

    SD2is sd2isBase(L, Nup, Ndn);
    sd2isBase.logwRef() = logw;
    sd2isBase.wfRef() = wf;

    SD2is sd2is(sd2isBase);
    EXPECT_COMPLEXDOUBLE_EQ( logw, sd2is.getLogw() );
    EXPECT_FALSE( diff( wf, sd2is.getWf(), 1e-12 ) );
    EXPECT_EQ( L, sd2is.getL() );
    EXPECT_EQ( Nup, sd2is.getNup() );
    EXPECT_EQ( Ndn, sd2is.getNdn() );
    EXPECT_FALSE( diff( wf, sd2isBase.getWf(), 1e-12 ) );
}

TEST(SD2isTest, moveConstruction)
{
    size_t L(10), Nup(5), Ndn(3);
    TensorHao<complex<double>,2> wf(L, max(Nup, Ndn) );
    randomFill(wf);
    complex<double> logw(2.0, 3.0);

    SD2is sd2isBase(L, Nup, Ndn);
    sd2isBase.logwRef() = logw;
    sd2isBase.wfRef() = wf;

    SD2is sd2is( move(sd2isBase) );
    EXPECT_COMPLEXDOUBLE_EQ( logw, sd2is.getLogw() );
    EXPECT_FALSE( diff( wf, sd2is.getWf(), 1e-12 ) );
    EXPECT_EQ( L, sd2is.getL() );
    EXPECT_EQ( Nup, sd2is.getNup() );
    EXPECT_EQ( Ndn, sd2is.getNdn() );
    EXPECT_FALSE( sd2isBase.getWf().data() );
}

TEST(SD2isTest, copyAssignment)
{
    size_t L(10), Nup(5), Ndn(3);
    TensorHao<complex<double>,2> wf(L, max(Nup, Ndn) );
    randomFill(wf);
    complex<double> logw(2.0, 3.0);

    SD2is sd2isBase(L, Nup, Ndn);
    sd2isBase.logwRef() = logw;
    sd2isBase.wfRef() = wf;

    SD2is sd2is; sd2is = sd2isBase;
    EXPECT_COMPLEXDOUBLE_EQ( logw, sd2is.getLogw() );
    EXPECT_FALSE( diff( wf, sd2is.getWf(), 1e-12 ) );
    EXPECT_EQ( L, sd2is.getL() );
    EXPECT_EQ( Nup, sd2is.getNup() );
    EXPECT_EQ( Ndn, sd2is.getNdn() );
    EXPECT_FALSE( diff( wf, sd2isBase.getWf(), 1e-12 ) );
}

TEST(SD2isTest, moveAssignment)
{
    size_t L(10), Nup(5), Ndn(3);
    TensorHao<complex<double>,2> wf(L, max(Nup, Ndn) );
    randomFill(wf);
    complex<double> logw(2.0, 3.0);

    SD2is sd2isBase(L, Nup, Ndn);
    sd2isBase.logwRef() = logw;
    sd2isBase.wfRef() = wf;

    SD2is sd2is; sd2is = move(sd2isBase);
    EXPECT_COMPLEXDOUBLE_EQ( logw, sd2is.getLogw() );
    EXPECT_FALSE( diff( wf, sd2is.getWf(), 1e-12 ) );
    EXPECT_EQ( L, sd2is.getL() );
    EXPECT_EQ( Nup, sd2is.getNup() );
    EXPECT_EQ( Ndn, sd2is.getNdn() );
    EXPECT_FALSE( sd2isBase.getWf().data() );
}

TEST(SD2isTest, readWriteBcast)
{
    size_t L(10), Nup(5), Ndn(3);
    TensorHao<complex<double>,2> wf(L, max(Nup, Ndn) );
    randomFill(wf);
    complex<double> logw(2.0, 3.0);

    SD2is sd2isBase(L, Nup, Ndn), sd2is;
    sd2isBase.logwRef() = logw;
    sd2isBase.wfRef() = wf;

    string filename="SD2is.dat";
    if( MPIRank() == 0 ) sd2isBase.write(filename);
    if( MPIRank() == 0 ) sd2is.read(filename);
    MPIBcast(sd2is);
    removeFile(filename);

    EXPECT_COMPLEXDOUBLE_EQ( logw, sd2is.getLogw() );
    EXPECT_FALSE( diff( wf, sd2is.getWf(), 1e-12 ) );
    EXPECT_EQ( L, sd2is.getL() );
    EXPECT_EQ( Nup, sd2is.getNup() );
    EXPECT_EQ( Ndn, sd2is.getNdn() );
}

#ifdef MPI_HAO
TEST(SD2isTest, packUnpack)
{
    size_t L(10), Nup(5), Ndn(3);
    TensorHao<complex<double>,2> wf(L, max(Nup, Ndn) );
    randomFill(wf);
    complex<double> logw(2.0, 3.0);

    SD2is sd2isBase(L, Nup, Ndn);
    sd2isBase.logwRef() = logw;
    sd2isBase.wfRef() = wf;

    SD2is sd2is; sd2is.resize(L, Nup, Ndn);

    int Nbuf = sd2isBase.returnNbuf();
    vector<char> buf(Nbuf);
    int posit(0); sd2isBase.pack(buf, posit);
    posit = 0; sd2is.unpack(buf, posit);

    EXPECT_COMPLEXDOUBLE_EQ( logw, sd2is.getLogw() );
    EXPECT_FALSE( diff( wf, sd2is.getWf(), 1e-12 ) );
    EXPECT_EQ( L, sd2is.getL() );
    EXPECT_EQ( Nup, sd2is.getNup() );
    EXPECT_EQ( Ndn, sd2is.getNdn() );
}
#endif

TEST(SD2isTest, normalize)
{
    size_t L(4), Nup(3), Ndn=2;
    SD2is sd2is(L,Nup, Ndn);
    sd2is.wfRef() = {{1.0,1.0}, {2.0,1.0}, {3.0,1.0}, {4.0,1.0},
                     {2.0,2.0}, {3.0,1.0}, {5.0,2.0}, {6.0,1.0},
                     {4.0,1.0}, {3.0,3.0}, {2.0,2.0}, {2.0,6.0} };

    complex<double> logw; double ratio;
    logw = sd2is.normalize(ratio);

    complex<double> logwExact(5.2382917510141205, 0.0);
    double ratioExact(0.19286583895005868);
    EXPECT_COMPLEXDOUBLE_EQ(logw, logwExact);
    EXPECT_DOUBLE_EQ(ratio, ratioExact);
}