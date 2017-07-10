//
// Created by boruoshihao on 7/8/17.
//

#ifndef AFQMCLAB_REALMATERIALMOLECULESD2SOPERATION_H
#define AFQMCLAB_REALMATERIALMOLECULESD2SOPERATION_H

#include "realMaterialMolecule.h"
#include "../../../blocks/walker/SD2s/include/SD2s.h"

void fillWalkerRandomly(SD2s &walker, const RealMaterialMolecule &model);
void fillWalkerFromModel(SD2s &walker, RealMaterialMolecule &model);

#endif //AFQMCLAB_REALMATERIALMOLECULESD2SOPERATION_H
