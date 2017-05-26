//
// Created by boruoshihao on 10/30/16.
//
#ifdef USE_OPENMP
#include <omp.h>
#endif

#include "../include/realMaterial.h"
#include "../../../../common/mathHao/include/simple_fun.h"

using namespace std;
using namespace tensor_hao;

void RealMaterial::applyHToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew) const
{
    applyOperatorsToWf(wf, wfNew, up, dn, upUp, upDn, dnDn);
}

void RealMaterial::applyKToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew) const
{
    vector<LanTwoBody> upUp,upDn,dnDn;
    applyOperatorsToWf(wf, wfNew, up, dn, upUp, upDn, dnDn);
}

void RealMaterial::applyVToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew) const
{
    vector<LanOneBody> up, dn;
    applyOperatorsToWf(wf, wfNew, up, dn, upUp, upDn, dnDn);
}

void RealMaterial::applySiSjToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew, size_t i, size_t j) const
{
    vector<LanOneBody> up, dn;
    vector<LanTwoBody> upUp,upDn,dnDn;

    if( i== j )
    {
        up.push_back( {i, i, 0.75} );
        dn.push_back( {i, i, 0.75} );
        upDn.push_back( {i, i, i, i, -1.5} );
    }
    else
    {
        upUp.push_back( {i,i,j,j, 0.25} );
        dnDn.push_back( {i,i,j,j, 0.25} );
        upDn.push_back( {i,i,j,j,-0.25} );
        upDn.push_back( {j,j,i,i,-0.25} );
        upDn.push_back( {i,j,j,i,-0.50} );
        upDn.push_back( {j,i,i,j,-0.50} );
    }

    applyOperatorsToWf(wf, wfNew, up, dn, upUp, upDn, dnDn);
}

void RealMaterial::applySziSzjToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew, size_t i, size_t j) const
{
    vector<LanOneBody> up, dn;
    vector<LanTwoBody> upUp,upDn,dnDn;

    if( i== j )
    {
        up.push_back( {i, i, 0.25} );
        dn.push_back( {i, i, 0.25} );
        upDn.push_back( {i, i, i, i, -0.5} );
    }
    else
    {
        upUp.push_back( {i,i,j,j, 0.25} );
        dnDn.push_back( {i,i,j,j, 0.25} );
        upDn.push_back( {i,i,j,j,-0.25} );
        upDn.push_back( {j,j,i,i,-0.25} );
    }

    applyOperatorsToWf(wf, wfNew, up, dn, upUp, upDn, dnDn);
}

void RealMaterial::applySplusiSminusjToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew, size_t i, size_t j) const
{
    vector<LanOneBody> up, dn;
    vector<LanTwoBody> upUp,upDn,dnDn;

    if( i== j ) up.push_back( {i, i, 1.0} );
    upDn.push_back( {i,j,j,i,-1.0} );

    applyOperatorsToWf(wf, wfNew, up, dn, upUp, upDn, dnDn);
}

void RealMaterial::applyNiNjToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew, size_t i, size_t j) const
{
    vector<LanOneBody> up, dn;
    vector<LanTwoBody> upUp,upDn,dnDn;

    if( i== j )
    {
        up.push_back( {i, i, 1.0} );
        dn.push_back( {i, i, 1.0} );
        upDn.push_back( {i, i, i, i, 2.0} );
    }
    else
    {
        upUp.push_back( {i, i, j, j, 1.0} );
        dnDn.push_back( {i, i, j, j, 1.0} );
        upDn.push_back( {i, i, j, j, 1.0} );
        upDn.push_back( {j, j, i, i, 1.0} );
    }

    applyOperatorsToWf(wf, wfNew, up, dn, upUp, upDn, dnDn);
}

void RealMaterial::applyDiDaggerDjToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew, size_t i, size_t j) const
{
    vector<LanOneBody> up, dn;
    vector<LanTwoBody> upUp,upDn,dnDn;

    upDn.push_back( {i,j,i,j, 1.0} );
    applyOperatorsToWf(wf, wfNew, up, dn, upUp, upDn, dnDn);
}

void RealMaterial::applyCupiDaggerCupjToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew, size_t i, size_t j) const
{
    vector<LanOneBody> up, dn;
    vector<LanTwoBody> upUp,upDn,dnDn;

    up.push_back( {i,j, 1.0} );
    applyOperatorsToWf(wf, wfNew, up, dn, upUp, upDn, dnDn);
}

void RealMaterial::applyCdniDaggerCdnjToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew, size_t i, size_t j) const
{
    vector<LanOneBody> up, dn;
    vector<LanTwoBody> upUp,upDn,dnDn;

    dn.push_back( {i,j, 1.0} );
    applyOperatorsToWf(wf, wfNew, up, dn, upUp, upDn, dnDn);
}

void RealMaterial::applyOperatorsToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew,
                                      const vector<LanOneBody> &up, const vector<LanOneBody> &dn,
                                      const vector<LanTwoBody> &upUp, const vector<LanTwoBody> &upDn,
                                      const vector<LanTwoBody> &dnDn) const
{
    if( wfNew.size() != wf.size() ) wfNew.resize( wf.size() );
    const TensorHao<complex<double>, 1> & vec = wf.getWf();
    TensorHao<complex<double>, 1> & vecNew = wfNew.wfRef();

    size_t numUp, numDn, numNew;
    TableElement tableElementOne, tableElementTwo;

#ifdef USE_OPENMP
    #pragma omp parallel for private(numUp, numDn, numNew, tableElementOne, tableElementTwo)
#endif
    for(size_t num = 0; num < NHilbert; ++num)
    {
        vecNew(num) = 0;

        numDn = num/NHilbertUp;
        numUp = num -numDn*NHilbertUp;
        for( const LanOneBody& oneBody : up )
        {
            tableElementOne = tableUp( oneBody.j, oneBody.i, numUp );
            if( tableElementOne.coefficient != 0 )
            {
                numNew = tableElementOne.index + numDn * NHilbertUp;
                vecNew(num) += tableElementOne.coefficient * 1.0 * oneBody.K *  vec(numNew);
            }
        }

        for( const LanOneBody& oneBody : dn )
        {
            tableElementOne = tableDn( oneBody.j, oneBody.i, numDn );
            if( tableElementOne.coefficient != 0 )
            {
                numNew = numUp + tableElementOne.index * NHilbertUp;
                vecNew(num) += tableElementOne.coefficient * 1.0 * oneBody.K *  vec(numNew);
            }
        }

        for( const LanTwoBody& twoBody : upUp )
        {
            tableElementOne = tableUp( twoBody.j, twoBody.i, numUp );
            if( tableElementOne.coefficient != 0 )
            {
                tableElementTwo = tableUp(twoBody.l, twoBody.k, tableElementOne.index);
                if( tableElementTwo.coefficient != 0 )
                {
                    numNew = tableElementTwo.index + numDn * NHilbertUp;
                    vecNew(num) += tableElementOne.coefficient * tableElementTwo.coefficient * 1.0
                                   * twoBody.V * vec(numNew);
                }
            }
        }

        for( const LanTwoBody& twoBody : upDn )
        {
            tableElementOne = tableUp( twoBody.j, twoBody.i, numUp );
            if( tableElementOne.coefficient != 0 )
            {
                tableElementTwo = tableDn(twoBody.l, twoBody.k, numDn);
                if( tableElementTwo.coefficient != 0 )
                {
                    numNew = tableElementOne.index + tableElementTwo.index * NHilbertUp;
                    vecNew(num) += tableElementOne.coefficient * tableElementTwo.coefficient * 1.0
                                   * twoBody.V * vec(numNew);
                }
            }
        }

        for( const LanTwoBody& twoBody : dnDn )
        {
            tableElementOne = tableDn( twoBody.j, twoBody.i, numDn );
            if( tableElementOne.coefficient != 0 )
            {
                tableElementTwo = tableDn(twoBody.l, twoBody.k, tableElementOne.index);
                if( tableElementTwo.coefficient != 0 )
                {
                    numNew = numUp + tableElementTwo.index * NHilbertUp;
                    vecNew(num) += tableElementOne.coefficient * tableElementTwo.coefficient * 1.0
                                   * twoBody.V * vec(numNew);
                }
            }
        }
    }
}

void RealMaterial::applyCupToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew,
                                const std::vector<LanOneOperator> &Cup) const
{
    size_t NewHilbertUp = binomialCoeff(L, Nup-1);
    size_t NewHilbertDn = NHilbertDn;
    size_t NewHilbert   = NewHilbertUp * NewHilbertDn;

    if( wfNew.size() != NewHilbert ) wfNew.resize( NewHilbert );
    const TensorHao<complex<double>, 1> & vec = wf.getWf();
    TensorHao<complex<double>, 1> & vecNew = wfNew.wfRef();

    TensorHao< TableElement, 2 > tableCup(L, NewHilbertUp);
    LanczosBasis lanBasisUp(L, Nup-1);
    for(size_t k = 0; k < NewHilbertUp; ++k)
    {
        for(size_t i = 0; i < L; ++i) tableCup(i, k) = lanBasisUp.getInfoByCiDagger(i);
        lanBasisUp.next();
    }

    size_t numUp, numDn, numNew;
    TableElement tableElement;
#ifdef USE_OPENMP
    #pragma omp parallel for private(numUp, numDn, numNew, tableElement)
#endif
    for(size_t num = 0; num < NewHilbert; ++num)
    {
        vecNew(num) = 0;

        numDn = num / NewHilbertUp;
        numUp = num - numDn * NewHilbertUp;

        for( const LanOneOperator& oneOperator : Cup )
        {
            tableElement = tableCup(oneOperator.i, numUp);
            numNew = tableElement.index + numDn * NHilbertUp;

            if( tableElement.coefficient != 0 )
            {
                vecNew(num) += tableElement.coefficient * 1.0 * oneOperator.C *  vec(numNew);
            }
        }
    }
}

void RealMaterial::applyCdnToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew,
                                const std::vector<LanOneOperator> &Cdn) const
{
    size_t NewHilbertUp = NHilbertUp;
    size_t NewHilbertDn = binomialCoeff(L, Ndn-1);
    size_t NewHilbert   = NewHilbertUp * NewHilbertDn;

    if( wfNew.size() != NewHilbert ) wfNew.resize( NewHilbert );
    const TensorHao<complex<double>, 1> & vec = wf.getWf();
    TensorHao<complex<double>, 1> & vecNew = wfNew.wfRef();

    TensorHao< TableElement, 2 > tableCdn(L, NewHilbertDn);
    LanczosBasis lanBasisDn(L, Ndn-1);
    for(size_t k = 0; k < NewHilbertDn; ++k)
    {
        for(size_t i = 0; i < L; ++i) tableCdn(i, k) = lanBasisDn.getInfoByCiDagger(i);
        lanBasisDn.next();
    }

    size_t numUp, numDn, numNew;
    TableElement tableElement;
#ifdef USE_OPENMP
    #pragma omp parallel for private(numUp, numDn, numNew, tableElement)
#endif
    for(size_t num = 0; num < NewHilbert; ++num)
    {
        vecNew(num) = 0;

        numDn = num / NewHilbertUp;
        numUp = num - numDn * NewHilbertUp;

        for( const LanOneOperator& oneOperator : Cdn )
        {
            tableElement = tableCdn(oneOperator.i, numDn);
            numNew = numUp + tableElement.index * NHilbertUp;

            if( tableElement.coefficient != 0 )
            {
                vecNew(num) += tableElement.coefficient * 1.0 * oneOperator.C *  vec(numNew);
            }
        }
    }
}

void RealMaterial::applyCupDaggerToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew,
                                      const std::vector<LanOneOperator> &Cup) const
{
    size_t NewHilbertUp = binomialCoeff(L, Nup+1);
    size_t NewHilbertDn = NHilbertDn;
    size_t NewHilbert   = NewHilbertUp * NewHilbertDn;

    if( wfNew.size() != NewHilbert ) wfNew.resize( NewHilbert );
    const TensorHao<complex<double>, 1> & vec = wf.getWf();
    TensorHao<complex<double>, 1> & vecNew = wfNew.wfRef();

    TensorHao< TableElement, 2 > tableCup(L, NewHilbertUp);
    LanczosBasis lanBasisUp(L, Nup+1);
    for(size_t k = 0; k < NewHilbertUp; ++k)
    {
        for(size_t i = 0; i < L; ++i) tableCup(i, k) = lanBasisUp.getInfoByCi(i);
        lanBasisUp.next();
    }

    size_t numUp, numDn, numNew;
    TableElement tableElement;
#ifdef USE_OPENMP
    #pragma omp parallel for private(numUp, numDn, numNew, tableElement)
#endif
    for(size_t num = 0; num < NewHilbert; ++num)
    {
        vecNew(num) = 0;

        numDn = num / NewHilbertUp;
        numUp = num - numDn * NewHilbertUp;

        for( const LanOneOperator& oneOperator : Cup )
        {
            tableElement = tableCup(oneOperator.i, numUp);
            numNew = tableElement.index + numDn * NHilbertUp;

            if( tableElement.coefficient != 0 )
            {
                vecNew(num) += tableElement.coefficient * 1.0 * oneOperator.C *  vec(numNew);
            }
        }
    }
}

void RealMaterial::applyCdnDaggerToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew,
                                      const std::vector<LanOneOperator> &Cdn) const
{
    size_t NewHilbertUp = NHilbertUp;
    size_t NewHilbertDn = binomialCoeff(L, Ndn+1);
    size_t NewHilbert   = NewHilbertUp * NewHilbertDn;

    if( wfNew.size() != NewHilbert ) wfNew.resize( NewHilbert );
    const TensorHao<complex<double>, 1> & vec = wf.getWf();
    TensorHao<complex<double>, 1> & vecNew = wfNew.wfRef();

    TensorHao< TableElement, 2 > tableCdn(L, NewHilbertDn);
    LanczosBasis lanBasisDn(L, Ndn+1);
    for(size_t k = 0; k < NewHilbertDn; ++k)
    {
        for(size_t i = 0; i < L; ++i) tableCdn(i, k) = lanBasisDn.getInfoByCi(i);
        lanBasisDn.next();
    }

    size_t numUp, numDn, numNew;
    TableElement tableElement;
#ifdef USE_OPENMP
    #pragma omp parallel for private(numUp, numDn, numNew, tableElement)
#endif
    for(size_t num = 0; num < NewHilbert; ++num)
    {
        vecNew(num) = 0;

        numDn = num / NewHilbertUp;
        numUp = num - numDn * NewHilbertUp;

        for( const LanOneOperator& oneOperator : Cdn )
        {
            tableElement = tableCdn(oneOperator.i, numDn);
            numNew = numUp + tableElement.index * NHilbertUp;

            if( tableElement.coefficient != 0 )
            {
                vecNew(num) += tableElement.coefficient * 1.0 * oneOperator.C *  vec(numNew);
            }
        }
    }
}