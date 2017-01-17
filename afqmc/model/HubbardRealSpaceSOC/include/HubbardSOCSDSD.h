//
// Created by boruoshihao on 1/17/17.
//

#ifndef AFQMCLAB_HUBBARDSOCSDSD_H
#define AFQMCLAB_HUBBARDSOCSDSD_H

#include "HubbardSOC.h"
#include "HubbardSOCSDSDMeasure.h"
#include "../../../blocks/oneBodyWalkerOperation/hopSDOperation/include/hopSDOperation.h"
#include "../../../blocks/twoBodyWalkerOperation/NiupNidnSDOperation/include/NiupNidnSDOperation.h"

void fillWalkerRandomly(SD &walker, const HubbardSOC &model);
void fillWalkerFromModel(SD &walker, HubbardSOC &model);
void fillWalkerFromModelIncludePinningField(SD &walker, HubbardSOC &model);
#endif //AFQMCLAB_HUBBARDSOCSDSD_H
