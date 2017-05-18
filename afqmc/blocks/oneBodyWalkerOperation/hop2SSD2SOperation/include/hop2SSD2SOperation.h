//
// Created by boruoshihao on 5/17/17.
//

#ifndef AFQMCLAB_HOP2SSD2SOPERATION_H
#define AFQMCLAB_HOP2SSD2SOPERATION_H

#include "../../../walker/SD2S/include/SD2S.h"
#include "../../../oneBodyOperator/hop2S/include/hop2S.h"

void applyOneBodyToRightWalker(const SD2S &walker, SD2S &walkerNew, const Hop2S &oneBody);
void applyOneBodyToLeftWalker(const SD2S &walker, SD2S &walkerNew, const Hop2S &oneBody);

#endif //AFQMCLAB_HOP2SSD2SOPERATION_H