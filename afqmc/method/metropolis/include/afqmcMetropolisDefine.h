//
// Created by boruoshihao on 1/15/17.
//

#ifndef AFQMCLAB_AFQMCMETROPOLISDEFINE_H
#define AFQMCLAB_AFQMCMETROPOLISDEFINE_H

#include "../../../../afqmclab.h"

typedef Hop OneBody;

typedef NiupNidn       TwoBody;
typedef NiupNidnAux    TwoBodyAux;
typedef NiupNidnForce  TwoBodyForce;
typedef NiupNidnSample TwoBodySample;

typedef HubbardSOC Model;

typedef SD  WalkerLeft;
typedef SD  WalkerRight;
typedef HopSDOperation OneBodyWalkerOperation;
typedef NiupNidnSampleSDOperation TwoBodyWalkerOperation;
typedef SDSDOperation WalkerWalkerOperation;
typedef HubbardSOCMeasureCommuteSDSD ModelMeasureCommute;
typedef HubbardSOCMeasureObserveSDSD ModelMeasureObserve;

#endif //AFQMCLAB_AFQMCMETROPOLISDEFINE_H
