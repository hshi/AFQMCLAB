//
// Created by boruoshihao on 12/28/16.
//

#include "../include/hoppingOperateSingleDeterminant.h"

using namespace std;
using namespace tensor_hao;

SingleDeterminant operator*(const HoppingOperator &A, const SingleDeterminant &B)
{
    SingleDeterminant C( B.getL(), B.getN() );
    BL_NAME(gmm)( A.getOp(), B.getWf(), C.wfRef() );
    return C;
}