//
// Created by boruoshihao on 12/28/16.
//

#include "../include/hopSingleDeterminantOperation.h"
#include "../../../../../common/testHao/gtest_custom.h"

using namespace std;
using namespace tensor_hao;

TEST(hopSingleDeterminantOperationTest, hoppingOperateSingleDeterminant)
{
    size_t L(10), N(5);
    TensorHao<complex<double>, 2> matrix(L,L), wf(L,N), wfNew(L,N);
    randomFill(matrix); randomFill(wf);
    gmm_cpu(matrix, wf, wfNew);

    SingleDeterminant sd(L,N), sdNew;
    Hop hop; hop.logw=1.2; hop.matrix=matrix;
    sd.logwRef()=1.6; sd.wfRef() = wf;
    applyOneBodyToRightWalker(sd, sdNew, hop);

    EXPECT_FALSE( diff(wfNew, sdNew.getWf(), 1e-12) );
    EXPECT_COMPLEXDOUBLE_EQ( 2.8, sdNew.getLogw() );
}