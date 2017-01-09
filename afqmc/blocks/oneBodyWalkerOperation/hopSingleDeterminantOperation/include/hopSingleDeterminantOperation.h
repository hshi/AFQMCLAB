//
// Created by boruoshihao on 12/28/16.
//

#ifndef AFQMCLAB_HOPSINGLEDETERMINANTOPERATION_H
#define AFQMCLAB_HOPSINGLEDETERMINANTOPERATION_H

#include "../../../walker/singleDeterminant/include/singleDeterminant.h"
#include "../../../oneBodyOperator/hop/include/Hop.h"

void applyOneBodyToRightWalker(const SingleDeterminant &walker, SingleDeterminant &walkerNew, const Hop &oneBody);
void applyOneBodyToLeftWalker(const SingleDeterminant &walker, SingleDeterminant &walkerNew, const Hop &oneBody);

#endif //AFQMCLAB_HOPSINGLEDETERMINANTOPERATION_H
