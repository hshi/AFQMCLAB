//
// Created by boruoshihao on 12/28/16.
//

#include "../include/hoppingOperateSingleDeterminant.h"

using namespace std;
using namespace tensor_hao;

void applyOneBodyToWalker(const SingleDeterminant &walker, SingleDeterminant &walkerNew, const HoppingOperator &oneBody)
{
    size_t L = walker.getL(); size_t N = walker.getN();
    if( oneBody.getL() !=  L ) {cout<<"Error!!! HoppingOperator size is not consistent with walker!"<<endl; exit(1); }
    if( walkerNew.getL() != L  ||  walkerNew.getN() != N ) walkerNew.wfRef().resize( L, N );

    BL_NAME(gmm)( oneBody.getOp(), walker.getWf(), walkerNew.wfRef() );
    walkerNew.logwRef() = oneBody.getLogw() + walker.getLogw();
}