//
// Created by boruoshihao on 1/14/17.
//

#ifndef AFQMCLAB_HUBBARDSOCSDSDDEFINE_H
#define AFQMCLAB_HUBBARDSOCSDSDDEFINE_H

#include "HubbardSOCSDSDMeasure.h"

typedef Hop OneBody;

typedef NiupNidn       TwoBody;
typedef NiupNidnAux    TwoBodyAux;
typedef NiupNidnForce  TwoBodyForce;
typedef NiupNidnSample TwoBodySample;

typedef HubbardSOC Model;

typedef SD  Walker;
typedef SDSDOperation WalkerWalkerOperation;
typedef HubbardSOCSDSDMeasure ModelCommuteMeasure;
typedef HubbardSOCSDSDMeasure ModelObserveMeasure;

#endif //AFQMCLAB_HUBBARDSOCSDSDDEFINE_H
