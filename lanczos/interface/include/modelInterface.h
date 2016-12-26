//
// Created by boruoshihao on 10/17/16.
//

#ifndef AFQMCLAB_MODELINTERFACE_H
#define AFQMCLAB_MODELINTERFACE_H

#include "LanczosBasisWf.h"

class ModelInterface
{
 public:
    virtual size_t getWfSize() const
    {
        return 0;
    };

    virtual void applyHToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew) const
    {
        if( wfNew.size() != wf.size() ) wfNew.resize( wf.size() );
    };

    virtual void projectSymmetry(LanczosBasisWf &wf) const
    {
    };
};

#endif //AFQMCLAB_MODELINTERFACE_H