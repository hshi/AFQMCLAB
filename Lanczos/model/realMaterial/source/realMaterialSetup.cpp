//
// Created by boruoshihao on 10/28/16.
//

#include "../include/realMaterial.h"

using namespace std;
using namespace tensor_hao;

void RealMaterial::setFromLNupNdn()
{
    LanczosBasis lanBasisUp(L, Nup), lanBasisDn(L, Ndn);

    setNHilbertUpAndTableUp(lanBasisUp);

    setNHilbertDnAndTableDn(lanBasisDn);

    NHilbert = NHilbertUp * NHilbertDn;

    printMemoryInfo();
}

void RealMaterial::setNHilbertUpAndTableUp(LanczosBasis &lanBasisUp)
{
    auto & binomialTable = lanBasisUp.getBinomialTable();
    NHilbertUp = binomialTable(L, Nup);
    tableUp.resize(L, L, NHilbertUp);

    for(size_t k = 0; k < NHilbertUp; ++k)
    {
        for(size_t j = 0; j < L; ++j)
        {
            for(size_t i = 0; i < L; ++i)
            {
                tableUp(i, j, k) = lanBasisUp.getInfoByCiDaggerCj(i, j);
            }
        }
        lanBasisUp.next();
    }
}

void RealMaterial::setNHilbertDnAndTableDn(LanczosBasis &lanBasisDn)
{
    auto & binomialTable = lanBasisDn.getBinomialTable();
    NHilbertDn = binomialTable(L, Ndn);
    tableDn.resize(L, L, NHilbertDn);

    for(size_t k = 0; k < NHilbertDn; ++k)
    {
        for(size_t j = 0; j < L; ++j)
        {
            for(size_t i = 0; i < L; ++i)
            {
                tableDn(i, j, k) = lanBasisDn.getInfoByCiDaggerCj(i, j);
            }
        }
        lanBasisDn.next();
    }
}

void RealMaterial::printMemoryInfo()
{
    double mem;
    cout<<endl;

    mem = ( sizeof(size_t) + sizeof(double) ) * NHilbertUp * L* L;
    cout<<"Memory for tableUp is "<<mem/1e9<<"GB"<<endl;

    mem = ( sizeof(size_t) + sizeof(double) ) * NHilbertDn * L* L;
    cout<<"Memory for tableDn is "<<mem/1e9<<"GB"<<endl;

    mem = sizeof(complex<double>) * NHilbert;
    cout<<"Memory for one Lanczos basis wave function is "<<mem/1e9<<"GB"<<endl;

    cout<<endl;
}