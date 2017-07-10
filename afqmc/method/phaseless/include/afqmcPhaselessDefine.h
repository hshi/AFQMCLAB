//
// Created by boruoshihao on 6/23/17.
//

#ifndef AFQMCLAB_AFQMCPHASELESSDEFINE_H
#define AFQMCLAB_AFQMCPHASELESSDEFINE_H

#include "../../../../afqmclab.h"

typedef Hop2is OneBody;
typedef LogHop2is LogOneBody;

typedef CholeskyReal       TwoBody;
typedef CholeskyRealAux    TwoBodyAux;
typedef CholeskyRealForce  TwoBodyForce;
typedef CholeskyRealSample TwoBodySample;

typedef RealMaterialMolecule Model;

typedef SD2s   WalkerLeft;
typedef SD2is  WalkerRight;
typedef Hop2isSD2isOperation OneBodyWalkerRightOperation;
typedef LogHop2isSD2isOperation LogOneBodyWalkerRightOperation;
typedef CholeskyRealSampleSD2isOperation TwoBodySampleWalkerRightOperation;
typedef SD2sSD2isOperation WalkerWalkerOperation;
typedef RealMaterialMoleculeFixedSD2sSD2is ModelMeasureMixedEstimator;

#endif //AFQMCLAB_AFQMCPHASELESSDEFINE_H