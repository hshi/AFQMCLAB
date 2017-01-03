//
// Created by boruoshihao on 12/28/16.
//

#include "../include/hoppingOperateSingleDeterminant.h"
#include "../../../../common/testHao/gtest_custom.h"

using namespace std;
using namespace tensor_hao;

TEST(oneBodyOperateWalkerTest, hoppingOperateSingleDeterminant)
{
    size_t L(10), N(5);
    TensorHao<complex<double>, 2> op(L,L), wf(L,N), wfNew(L,N);
    randomFill(op); randomFill(wf);
    gmm_cpu(op, wf, wfNew);

    SingleDeterminant sd(L,N), sdNew;
    HoppingOperator ho(1.2, op);
    sd.logwRef()=1.6; sd.wfRef() = wf;
    applyOneBodyToWalker(sd, sdNew, ho);

    EXPECT_FALSE( diff(wfNew, sdNew.getWf(), 1e-12) );
    EXPECT_COMPLEXDOUBLE_EQ( 2.8, sdNew.getLogw() );
}