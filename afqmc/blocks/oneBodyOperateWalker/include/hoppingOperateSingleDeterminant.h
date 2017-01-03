//
// Created by boruoshihao on 12/28/16.
//

#ifndef AFQMCLAB_HOPPINGOPERATESINGLEDETERMINANT_H
#define AFQMCLAB_HOPPINGOPERATESINGLEDETERMINANT_H

#include "../../walker/include/singleDeterminant.h"
#include "../../oneBodyOperator/include/hoppingOperator.h"

void applyOneBodyToWalker(const SingleDeterminant& walker, SingleDeterminant& walkerNew, const HoppingOperator& A);

#endif //AFQMCLAB_HOPPINGOPERATESINGLEDETERMINANT_H
