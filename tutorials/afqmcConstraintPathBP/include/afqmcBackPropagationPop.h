//
// Created by Hao Shi on 8/4/17.
//

#ifndef AFQMCCONSTRAINTPATH_AFQMCBACKPROPAGATIONPOP_H
#define AFQMCCONSTRAINTPATH_AFQMCBACKPROPAGATIONPOP_H

#include "afqmcConstraintPathDefine.h"

class AfqmcBackPropagationPop
{
    int Nbuf;
    size_t BPNumber;
    std::vector<TwoBodyAux> *twoBodyAuxBPMeasure;
    WalkerRight * walkerBPMeasure;

 public:
    AfqmcBackPropagationPop();
    AfqmcBackPropagationPop(size_t BPNumber_in, std::vector<TwoBodyAux> &twoBodyAuxBPMeasure_in, WalkerRight& walkerBPMeasure_in);
    ~AfqmcBackPropagationPop();

    int getNbuf() const;

    AfqmcBackPropagationPop& operator  = (const AfqmcBackPropagationPop& x);
#ifdef MPI_HAO
    std::vector<char> pack() const;
    void unpack(const std::vector<char>& buf);
#endif

 private:
    void setNbuf();
};


#endif //AFQMCCONSTRAINTPATH_AFQMCBACKPROPAGATIONPOP_H
