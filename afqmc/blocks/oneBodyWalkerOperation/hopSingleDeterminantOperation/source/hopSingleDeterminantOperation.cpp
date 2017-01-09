//
// Created by boruoshihao on 12/28/16.
//

#include "../include/hopSingleDeterminantOperation.h"

using namespace std;
using namespace tensor_hao;

void applyOneBodyToRightWalker(const SingleDeterminant &walker, SingleDeterminant &walkerNew, const Hop &oneBody)
{
    size_t L = walker.getL(); size_t N = walker.getN();
    if( oneBody.getL() !=  L ) {cout<<"Error!!! Hop size is not consistent with walker!"<<endl; exit(1); }
    if( walkerNew.getL() != L  ||  walkerNew.getN() != N ) walkerNew.wfRef().resize( L, N );

    BL_NAME(gmm)( oneBody.matrix, walker.getWf(), walkerNew.wfRef() );
    walkerNew.logwRef() = oneBody.logw + walker.getLogw();
}

void applyOneBodyToLeftWalker(const SingleDeterminant &walker, SingleDeterminant &walkerNew, const Hop &oneBody)
{
    size_t L = walker.getL(); size_t N = walker.getN();
    if( oneBody.getL() !=  L ) {cout<<"Error!!! Hop size is not consistent with walker!"<<endl; exit(1); }
    if( walkerNew.getL() != L  ||  walkerNew.getN() != N ) walkerNew.wfRef().resize( L, N );

    BL_NAME(gmm)( oneBody.matrix, walker.getWf(), walkerNew.wfRef(), 'C' );
    walkerNew.logwRef() = conj( oneBody.logw ) + walker.getLogw();
}