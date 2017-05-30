//
// Created by boruoshihao on 05/18/17.
//

#ifndef AFQMCLAB_HOP2ISSD2ISOPERATION_H
#define AFQMCLAB_HOP2ISSD2ISOPERATION_H

#include "../../../walker/SD2is/include/SD2is.h"
#include "../../../oneBodyOperator/hop2is/include/hop2is.h"

class Hop2isSD2isOperation
{
 public:
    Hop2isSD2isOperation();
    ~Hop2isSD2isOperation();

    void applyToRight(const Hop2is &oneBody, const SD2is &walker, SD2is &walkerNew) const;
    void applyToLeft(const Hop2is &oneBody, const SD2is &walker, SD2is &walkerNew) const;

 private:
    void checkAndResize(const Hop2is &oneBody, const SD2is &walker, SD2is &walkerNew) const;
};

#endif //AFQMCLAB_HOP2ISSD2ISOPERATION_H
