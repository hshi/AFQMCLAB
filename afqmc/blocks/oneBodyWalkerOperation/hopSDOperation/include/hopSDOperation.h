//
// Created by boruoshihao on 12/28/16.
//

#ifndef AFQMCLAB_HOPSINGLEDETERMINANTOPERATION_H
#define AFQMCLAB_HOPSINGLEDETERMINANTOPERATION_H

#include "../../../walker/SD/include/SD.h"
#include "../../../oneBodyOperator/hop/include/Hop.h"

void applyOneBodyToRightWalker(const SD &walker, SD &walkerNew, const Hop &oneBody);
void applyOneBodyToLeftWalker(const SD &walker, SD &walkerNew, const Hop &oneBody);

#endif //AFQMCLAB_HOPSINGLEDETERMINANTOPERATION_H
