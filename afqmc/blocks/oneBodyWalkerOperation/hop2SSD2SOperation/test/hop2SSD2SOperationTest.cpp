//
// Created by boruoshihao on 5/17/17.
//

#include "../include/hop2SSD2SOperation.h"
#include "../../../../../common/testHao/gtest_custom.h"

using namespace std;
using namespace tensor_hao;

TEST(hop2SSD2SOperationTest, applyOneBodyToRightWalker)
{
    size_t L(10), Nup(5), Ndn(3);
    TensorHao<complex<double>, 2> matrixUp(L,L), wfUp(L,Nup), wfUpNew(L,Nup);
    TensorHao<complex<double>, 2> matrixDn(L,L), wfDn(L,Ndn), wfDnNew(L,Ndn);
    randomFill(matrixUp); randomFill(wfUp);
    randomFill(matrixDn); randomFill(wfDn);
    gmm_cpu(matrixUp, wfUp, wfUpNew);
    gmm_cpu(matrixDn, wfDn, wfDnNew);

    SD2S sd2S(L,Nup, Ndn), sd2SNew;
    Hop2S hop2S; hop2S.logw=complex<double>(1.2,1.5); hop2S.matrixUp=matrixUp; hop2S.matrixDn = matrixDn;
    sd2S.logwRef()=1.6; sd2S.wfUpRef() = wfUp; sd2S.wfDnRef() = wfDn;
    applyOneBodyToRightWalker(sd2S, sd2SNew, hop2S);

    EXPECT_FALSE( diff(wfUpNew, sd2SNew.getWfUp(), 1e-12) );
    EXPECT_FALSE( diff(wfDnNew, sd2SNew.getWfDn(), 1e-12) );
    EXPECT_COMPLEXDOUBLE_EQ( complex<double>(2.8, 1.5), sd2SNew.getLogw() );
}

TEST(hop2SSD2SOperationTest, applyOneBodyToLeftWalker)
{
    size_t L(10), Nup(5), Ndn(3);
    TensorHao<complex<double>, 2> matrixUp(L,L), wfUp(L,Nup), wfUpNew(L,Nup);
    TensorHao<complex<double>, 2> matrixDn(L,L), wfDn(L,Ndn), wfDnNew(L,Ndn);
    randomFill(matrixUp); randomFill(wfUp);
    randomFill(matrixDn); randomFill(wfDn);
    gmm_cpu(matrixUp, wfUp, wfUpNew, 'C');
    gmm_cpu(matrixDn, wfDn, wfDnNew, 'C');

    SD2S sd2S(L,Nup, Ndn), sd2SNew;
    Hop2S hop2S; hop2S.logw=complex<double>(1.2,1.5); hop2S.matrixUp=matrixUp; hop2S.matrixDn = matrixDn;
    sd2S.logwRef()=1.6; sd2S.wfUpRef() = wfUp; sd2S.wfDnRef() = wfDn;
    applyOneBodyToLeftWalker(sd2S, sd2SNew, hop2S);

    EXPECT_FALSE( diff(wfUpNew, sd2SNew.getWfUp(), 1e-12) );
    EXPECT_FALSE( diff(wfDnNew, sd2SNew.getWfDn(), 1e-12) );
    EXPECT_COMPLEXDOUBLE_EQ( complex<double>(2.8, -1.5), sd2SNew.getLogw() );
}