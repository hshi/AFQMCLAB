//
// Created by boruoshihao on 5/17/17.
//

#include "../include/hop2sSD2sOperation.h"

using namespace std;
using namespace tensor_hao;

void applyOneBodyToRightWalker(const SD2s &walker, SD2s &walkerNew, const Hop2s &oneBody)
{
    size_t L = walker.getL(); size_t Nup = walker.getNup(); size_t Ndn = walker.getNdn();
    if( oneBody.getL() !=  L ) {cout<<"Error!!! Hop2s size is not consistent with walker!"<<endl; exit(1); }
    if( walkerNew.getL() != L  ||  walkerNew.getNup() != Nup || walkerNew.getNdn() != Ndn ) walkerNew.resize(L, Nup, Ndn);

    BL_NAME(gmm)( oneBody.matrixUp, walker.getWfUp(), walkerNew.wfUpRef() );
    BL_NAME(gmm)( oneBody.matrixDn, walker.getWfDn(), walkerNew.wfDnRef() );
    walkerNew.logwRef() = oneBody.logw + walker.getLogw();
}

void applyOneBodyToLeftWalker(const SD2s &walker, SD2s &walkerNew, const Hop2s &oneBody)
{
    size_t L = walker.getL(); size_t Nup = walker.getNup(); size_t Ndn = walker.getNdn();
    if( oneBody.getL() !=  L ) {cout<<"Error!!! Hop2s size is not consistent with walker!"<<endl; exit(1); }
    if( walkerNew.getL() != L  ||  walkerNew.getNup() != Nup || walkerNew.getNdn() != Ndn ) walkerNew.resize(L, Nup, Ndn);

    BL_NAME(gmm)( oneBody.matrixUp, walker.getWfUp(), walkerNew.wfUpRef(), 'C' );
    BL_NAME(gmm)( oneBody.matrixDn, walker.getWfDn(), walkerNew.wfDnRef(), 'C' );
    walkerNew.logwRef() = conj( oneBody.logw ) + walker.getLogw();
}