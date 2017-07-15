//
// Created by boruoshihao on 7/9/17.
//

#ifndef AFQMCLAB_AFQMCWALKERPOP_H
#define AFQMCLAB_AFQMCWALKERPOP_H

#include "afqmcPhaseless.h"

class AfqmcWalkerPop
{
    int Nbuf;
    WalkerRight * walkerRight;

 public:
    AfqmcWalkerPop();
    AfqmcWalkerPop(WalkerRight& walkerRight_in);
    ~AfqmcWalkerPop();

    int getNbuf() const;

    AfqmcWalkerPop& operator  = (const AfqmcWalkerPop& x);
#ifdef MPI_HAO
    std::vector<char> pack() const;
    void unpack(const std::vector<char>& buf);
#endif

 private:
    void setNbuf();
};


#endif //AFQMCLAB_AFQMCWALKERPOP_H
