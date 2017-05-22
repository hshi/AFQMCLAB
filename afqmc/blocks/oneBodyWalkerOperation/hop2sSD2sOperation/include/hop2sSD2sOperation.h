//
// Created by boruoshihao on 5/17/17.
//

#ifndef AFQMCLAB_HOP2SSD2SOPERATION_H
#define AFQMCLAB_HOP2SSD2SOPERATION_H

#include "../../../walker/SD2s/include/SD2s.h"
#include "../../../oneBodyOperator/hop2s/include/hop2s.h"

void applyOneBodyToRightWalker(const SD2s &walker, SD2s &walkerNew, const Hop2s &oneBody);
void applyOneBodyToLeftWalker(const SD2s &walker, SD2s &walkerNew, const Hop2s &oneBody);

#endif //AFQMCLAB_HOP2SSD2SOPERATION_H
