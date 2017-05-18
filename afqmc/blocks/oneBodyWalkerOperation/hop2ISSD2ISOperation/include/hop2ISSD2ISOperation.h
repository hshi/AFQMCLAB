//
// Created by boruoshihao on 05/18/17.
//

#ifndef AFQMCLAB_HOP2ISSD2ISOPERATION_H
#define AFQMCLAB_HOP2ISSD2ISOPERATION_H

#include "../../../walker/SD2IS/include/SD2IS.h"
#include "../../../oneBodyOperator/hop2IS/include/hop2IS.h"

void applyOneBodyToRightWalker(const SD2IS &walker, SD2IS &walkerNew, const Hop2IS &oneBody);
void applyOneBodyToLeftWalker(const SD2IS &walker, SD2IS &walkerNew, const Hop2IS &oneBody);

#endif //AFQMCLAB_HOP2ISSD2ISOPERATION_H
