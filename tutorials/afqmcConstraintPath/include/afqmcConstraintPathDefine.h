//
// Created by boruoshihao on 4/16/17.
//

#ifndef AFQMCLAB_AFQMCCONSTRAINTPATHDEFINE_H
#define AFQMCLAB_AFQMCCONSTRAINTPATHDEFINE_H

#include "afqmclab.h"

typedef Hop OneBody;

typedef NiupNidn       TwoBody;
typedef NiupNidnAux    TwoBodyAux;
typedef NiupNidnForce  TwoBodyForce;
typedef NiupNidnSample TwoBodySample;

typedef HubbardSOC Model;

typedef SD  WalkerLeft;
typedef SD  WalkerRight;
typedef SDSDOperation WalkerWalkerOperation;
typedef HubbardSOCSDSDMeasureCommute ModelCommuteMeasure;

#endif //AFQMCLAB_AFQMCCONSTRAINTPATHDEFINE_H