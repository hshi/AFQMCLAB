//
// Created by boruoshihao on 1/15/17.
//

#ifndef AFQMCLAB_AFQMCMETROPOLISDEFINE_H
#define AFQMCLAB_AFQMCMETROPOLISDEFINE_H

#include "../../../afqmc.h"

typedef Hop OneBody;

typedef NiupNidn       TwoBody;
typedef NiupNidnAux    TwoBodyAux;
typedef NiupNidnForce  TwoBodyForce;
typedef NiupNidnSample TwoBodySample;

typedef HubbardSOC Model;

typedef SD  WalkerLeft;
typedef SD  WalkerRight;
typedef SDSDOperation WalkerWalkerOperation;
typedef HubbardSOCSDSDMeasure ModelCommuteMeasure;
typedef HubbardSOCSDSDMeasure ModelObserveMeasure;

#endif //AFQMCLAB_AFQMCMETROPOLISDEFINE_H
