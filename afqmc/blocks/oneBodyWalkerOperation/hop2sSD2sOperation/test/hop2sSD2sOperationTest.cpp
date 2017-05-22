//
// Created by boruoshihao on 5/17/17.
//

#include "../include/hop2sSD2sOperation.h"
#include "../../../../../common/testHao/gtest_custom.h"

using namespace std;
using namespace tensor_hao;

TEST(hop2sSD2sOperationTest, applyOneBodyToRightWalker)
{
    size_t L(10), Nup(5), Ndn(3);
    TensorHao<complex<double>, 2> matrixUp(L,L), wfUp(L,Nup), wfUpNew(L,Nup);
    TensorHao<complex<double>, 2> matrixDn(L,L), wfDn(L,Ndn), wfDnNew(L,Ndn);
    randomFill(matrixUp); randomFill(wfUp);
    randomFill(matrixDn); randomFill(wfDn);
    gmm_cpu(matrixUp, wfUp, wfUpNew);
    gmm_cpu(matrixDn, wfDn, wfDnNew);

    SD2s sd2s(L,Nup, Ndn), sd2sNew;
    Hop2s hop2s; hop2s.logw=complex<double>(1.2,1.5); hop2s.matrixUp=matrixUp; hop2s.matrixDn = matrixDn;
    sd2s.logwRef()=1.6; sd2s.wfUpRef() = wfUp; sd2s.wfDnRef() = wfDn;
    applyOneBodyToRightWalker(sd2s, sd2sNew, hop2s);

    EXPECT_FALSE( diff(wfUpNew, sd2sNew.getWfUp(), 1e-12) );
    EXPECT_FALSE( diff(wfDnNew, sd2sNew.getWfDn(), 1e-12) );
    EXPECT_COMPLEXDOUBLE_EQ( complex<double>(2.8, 1.5), sd2sNew.getLogw() );
}

TEST(hop2sSD2sOperationTest, applyOneBodyToLeftWalker)
{
    size_t L(10), Nup(5), Ndn(3);
    TensorHao<complex<double>, 2> matrixUp(L,L), wfUp(L,Nup), wfUpNew(L,Nup);
    TensorHao<complex<double>, 2> matrixDn(L,L), wfDn(L,Ndn), wfDnNew(L,Ndn);
    randomFill(matrixUp); randomFill(wfUp);
    randomFill(matrixDn); randomFill(wfDn);
    gmm_cpu(matrixUp, wfUp, wfUpNew, 'C');
    gmm_cpu(matrixDn, wfDn, wfDnNew, 'C');

    SD2s sd2s(L,Nup, Ndn), sd2sNew;
    Hop2s hop2s; hop2s.logw=complex<double>(1.2,1.5); hop2s.matrixUp=matrixUp; hop2s.matrixDn = matrixDn;
    sd2s.logwRef()=1.6; sd2s.wfUpRef() = wfUp; sd2s.wfDnRef() = wfDn;
    applyOneBodyToLeftWalker(sd2s, sd2sNew, hop2s);

    EXPECT_FALSE( diff(wfUpNew, sd2sNew.getWfUp(), 1e-12) );
    EXPECT_FALSE( diff(wfDnNew, sd2sNew.getWfDn(), 1e-12) );
    EXPECT_COMPLEXDOUBLE_EQ( complex<double>(2.8, -1.5), sd2sNew.getLogw() );
}
