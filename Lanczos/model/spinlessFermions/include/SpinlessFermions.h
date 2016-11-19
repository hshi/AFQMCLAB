//
// Created by boruoshihao on 11/18/16.
//

#ifndef AFQMCLIB_SPINLESSFERMIONS_H
#define AFQMCLIB_SPINLESSFERMIONS_H

#include "../../../interface/include/modelInterface.h"
#include "../../../interface/include/LanczosBasisWf.h"
#include "../../lanczosBasis/include/lanczosBasis.h"

class SpinlessFermions : public ModelInterface
{
    size_t L, N;
    std::vector<LanOneBody> K;
    std::vector<LanTwoBody> V;
    size_t Nhilbert;
};

#endif //AFQMCLIB_SPINLESSFERMIONS_H
