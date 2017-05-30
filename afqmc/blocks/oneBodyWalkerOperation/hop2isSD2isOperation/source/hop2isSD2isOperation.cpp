//
// Created by boruoshihao on 12/28/16.
//

#include "../include/hop2isSD2isOperation.h"

using namespace std;
using namespace tensor_hao;

Hop2isSD2isOperation::Hop2isSD2isOperation() { }

Hop2isSD2isOperation::~Hop2isSD2isOperation() { }

void Hop2isSD2isOperation::applyToRight(const Hop2is &oneBody, const SD2is &walker, SD2is &walkerNew) const
{
    checkAndResize(oneBody, walker, walkerNew);
    BL_NAME(gmm)( oneBody.matrix, walker.getWf(), walkerNew.wfRef() );
    walkerNew.logwRef() = oneBody.logw + walker.getLogw();
}

void Hop2isSD2isOperation::applyToLeft(const Hop2is &oneBody, const SD2is &walker, SD2is &walkerNew) const
{
    checkAndResize(oneBody, walker, walkerNew);
    BL_NAME(gmm)( oneBody.matrix, walker.getWf(), walkerNew.wfRef(), 'C' );
    walkerNew.logwRef() = conj( oneBody.logw ) + walker.getLogw();
}

void Hop2isSD2isOperation::checkAndResize(const Hop2is &oneBody, const SD2is &walker, SD2is &walkerNew) const
{
    size_t L = walker.getL(); size_t Nup = walker.getNup(); size_t Ndn = walker.getNdn();
    if( oneBody.getL() !=  L ) {cout<<"Error!!! Hop2is size is not consistent with walker!"<<endl; exit(1); }
    if( walkerNew.getL() != L  ||  walkerNew.getNup() != Nup || walkerNew.getNdn() != Ndn ) walkerNew.resize( L, Nup, Ndn );
}