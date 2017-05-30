//
// Created by boruoshihao on 5/17/17.
//

#ifndef AFQMCLAB_HOP2SSD2SOPERATION_H
#define AFQMCLAB_HOP2SSD2SOPERATION_H

#include "../../../walker/SD2s/include/SD2s.h"
#include "../../../oneBodyOperator/hop2s/include/hop2s.h"

class Hop2sSD2sOperation
{
 public:
    Hop2sSD2sOperation();
    ~Hop2sSD2sOperation();

    void applyToRight(const Hop2s &oneBody, const SD2s &walker, SD2s &walkerNew) const;
    void applyToLeft(const Hop2s &oneBody, const SD2s &walker, SD2s &walkerNew) const;

 private:
    void checkAndResize(const Hop2s &oneBody, const SD2s &walker, SD2s &walkerNew) const;
};

#endif //AFQMCLAB_HOP2SSD2SOPERATION_H
