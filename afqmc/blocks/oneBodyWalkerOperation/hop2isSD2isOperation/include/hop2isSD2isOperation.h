//
// Created by boruoshihao on 05/18/17.
//

#ifndef AFQMCLAB_HOP2ISSD2ISOPERATION_H
#define AFQMCLAB_HOP2ISSD2ISOPERATION_H

#include "../../../walker/SD2is/include/SD2is.h"
#include "../../../oneBodyOperator/hop2is/include/hop2is.h"

void applyOneBodyToRightWalker(const SD2is &walker, SD2is &walkerNew, const Hop2is &oneBody);
void applyOneBodyToLeftWalker(const SD2is &walker, SD2is &walkerNew, const Hop2is &oneBody);

#endif //AFQMCLAB_HOP2ISSD2ISOPERATION_H
