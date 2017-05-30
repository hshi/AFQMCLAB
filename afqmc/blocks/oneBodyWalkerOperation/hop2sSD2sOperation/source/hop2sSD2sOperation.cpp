//
// Created by boruoshihao on 5/17/17.
//

#include "../include/hop2sSD2sOperation.h"

using namespace std;
using namespace tensor_hao;

Hop2sSD2sOperation::Hop2sSD2sOperation() { }

Hop2sSD2sOperation::~Hop2sSD2sOperation() { }

void Hop2sSD2sOperation::applyToRight(const Hop2s &oneBody, const SD2s &walker, SD2s &walkerNew) const
{
    checkAndResize(oneBody, walker, walkerNew);
    BL_NAME(gmm)( oneBody.matrixUp, walker.getWfUp(), walkerNew.wfUpRef() );
    BL_NAME(gmm)( oneBody.matrixDn, walker.getWfDn(), walkerNew.wfDnRef() );
    walkerNew.logwRef() = oneBody.logw + walker.getLogw();
}

void Hop2sSD2sOperation::applyToLeft(const Hop2s &oneBody, const SD2s &walker, SD2s &walkerNew) const
{
    checkAndResize(oneBody, walker, walkerNew);
    BL_NAME(gmm)( oneBody.matrixUp, walker.getWfUp(), walkerNew.wfUpRef(), 'C' );
    BL_NAME(gmm)( oneBody.matrixDn, walker.getWfDn(), walkerNew.wfDnRef(), 'C' );
    walkerNew.logwRef() = conj( oneBody.logw ) + walker.getLogw();
}

void Hop2sSD2sOperation::checkAndResize(const Hop2s &oneBody, const SD2s &walker, SD2s &walkerNew) const
{
    size_t L = walker.getL(); size_t Nup = walker.getNup(); size_t Ndn = walker.getNdn();
    if( oneBody.getL() !=  L ) {cout<<"Error!!! Hop2s size is not consistent with walker!"<<endl; exit(1); }
    if( walkerNew.getL() != L  ||  walkerNew.getNup() != Nup || walkerNew.getNdn() != Ndn ) walkerNew.resize(L, Nup, Ndn);
}