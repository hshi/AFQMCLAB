//
// Created by boruoshihao on 12/28/16.
//

#ifndef AFQMCLAB_HOPSINGLEDETERMINANTOPERATION_H
#define AFQMCLAB_HOPSINGLEDETERMINANTOPERATION_H

#include "../../../walker/SD/include/SD.h"
#include "../../../oneBodyOperator/hop/include/hop.h"

class HopSDOperation
{
 public:
    HopSDOperation();
    ~HopSDOperation();

    void applyToRight(const Hop &oneBody, const SD &walker, SD &walkerNew) const;
    void applyToLeft(const Hop &oneBody, const SD &walker, SD &walkerNew) const;

 private:
    void checkAndResize(const Hop &oneBody, const SD &walker, SD &walkerNew) const;
};

#endif //AFQMCLAB_HOPSINGLEDETERMINANTOPERATION_H
