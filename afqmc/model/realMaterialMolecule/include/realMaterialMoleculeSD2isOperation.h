//
// Created by boruoshihao on 7/8/17.
//

#ifndef AFQMCLAB_REALMATERIALMOLECULESD2ISOPERATION_H
#define AFQMCLAB_REALMATERIALMOLECULESD2ISOPERATION_H

#include "realMaterialMolecule.h"
#include "../../../blocks/walker/SD2is/include/SD2is.h"

void fillWalkerRandomly(SD2is &walker, const RealMaterialMolecule &model);
void fillWalkerFromModel(SD2is &walker, RealMaterialMolecule &model);

#endif //AFQMCLAB_REALMATERIALMOLECULESD2ISOPERATION_H
