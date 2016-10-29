//
// Created by boruoshihao on 10/28/16.
//

#include "realMaterial.h"
#include "../../../libhao/math_hao/include/simple_fun.h"

using namespace std;
using namespace tensor_hao;

void RealMaterial::setSizeofHilbertSpace()
{
    NHilbertUp = binomialCoeff(L, Nup);
    NHilbertDn = binomialCoeff(L, Ndn);
    NHilbert   = NHilbertUp * NHilbertDn;
}

void RealMaterial::resizeTable()
{
    double mem;

    tableUp.resize(NHilbertUp, L, L);
    mem = ( sizeof(size_t) + sizeof(double) ) * NHilbertUp * L* L;
    cout<<"Memory for tableUp is "<<mem/1e9<<"GB"<<endl;

    tableDn.resize(NHilbertDn, L, L);
    mem = ( sizeof(size_t) + sizeof(double) ) * NHilbertDn * L* L;
    cout<<"Memory for tableDn is "<<mem/1e9<<"GB"<<endl;
}
