//
// Created by boruoshihao on 12/28/16.
//

#include "../include/hop2ISSD2ISOperation.h"

using namespace std;
using namespace tensor_hao;

void applyOneBodyToRightWalker(const SD2IS &walker, SD2IS &walkerNew, const Hop2IS &oneBody)
{
    size_t L = walker.getL(); size_t Nup = walker.getNup(); size_t Ndn = walker.getNdn();
    if( oneBody.getL() !=  L ) {cout<<"Error!!! Hop2IS size is not consistent with walker!"<<endl; exit(1); }
    if( walkerNew.getL() != L  ||  walkerNew.getNup() != Nup || walkerNew.getNdn() != Ndn ) walkerNew.resize( L, Nup, Ndn );

    BL_NAME(gmm)( oneBody.matrix, walker.getWf(), walkerNew.wfRef() );
    walkerNew.logwRef() = oneBody.logw + walker.getLogw();
}

void applyOneBodyToLeftWalker(const SD2IS &walker, SD2IS &walkerNew, const Hop2IS &oneBody)
{
    size_t L = walker.getL(); size_t Nup = walker.getNup(); size_t Ndn = walker.getNdn();
    if( oneBody.getL() !=  L ) {cout<<"Error!!! Hop2IS size is not consistent with walker!"<<endl; exit(1); }
    if( walkerNew.getL() != L  ||  walkerNew.getNup() != Nup || walkerNew.getNdn() != Ndn ) walkerNew.resize( L, Nup, Ndn );

    BL_NAME(gmm)( oneBody.matrix, walker.getWf(), walkerNew.wfRef(), 'C' );
    walkerNew.logwRef() = conj( oneBody.logw ) + walker.getLogw();
}
