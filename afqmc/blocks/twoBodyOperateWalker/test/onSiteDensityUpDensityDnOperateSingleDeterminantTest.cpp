//
// Created by boruoshihao on 1/9/17.
//

#include "../include/onSiteDensityUpDensityDnOperateSingleDeterminant.h"
#include "../../../../common/testHao/gtest_custom.h"

using namespace std;
using namespace tensor_hao;

TEST(oneBodyOperateWalkerTest, hoppingOperateSingleDeterminant)
{
    size_t L(10), N(5);
    TensorHao<complex<double>, 2> op(L,L), wf(L,N), wfNew(L,N);
    randomFill(op); randomFill(wf);
}