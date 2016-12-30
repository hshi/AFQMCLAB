//
// Created by boruoshihao on 12/28/16.
//

#ifndef AFQMCLAB_HOPPINGOPERATESINGLEDETERMINANT_H
#define AFQMCLAB_HOPPINGOPERATESINGLEDETERMINANT_H

#include "../../walker/include/singleDeterminant.h"
#include "../../oneBodyOperator/include/hoppingOperator.h"

SingleDeterminant operator * (const HoppingOperator& A,  const SingleDeterminant& B);

#endif //AFQMCLAB_HOPPINGOPERATESINGLEDETERMINANT_H
