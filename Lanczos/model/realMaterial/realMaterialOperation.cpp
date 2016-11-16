//
// Created by boruoshihao on 10/30/16.
//

#include "realMaterial.h"

using namespace std;
using namespace tensor_hao;

void RealMaterial::applyHToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew) const
{
    applyOperatorsToWf(wf, wfNew, up, dn, upUp, upDn, dnDn);
}

void RealMaterial::applyKToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew) const
{
    vector<TwoBody> upUp,upDn,dnDn;
    applyOperatorsToWf(wf, wfNew, up, dn, upUp, upDn, dnDn);
}

void RealMaterial::applyVToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew) const
{
    vector<OneBody> up, dn;
    applyOperatorsToWf(wf, wfNew, up, dn, upUp, upDn, dnDn);
}

void RealMaterial::applySiSjToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew, size_t i, size_t j) const
{
    vector<OneBody> up, dn;
    vector<TwoBody> upUp,upDn,dnDn;

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
    vector<OneBody> up, dn;
    vector<TwoBody> upUp,upDn,dnDn;

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
    vector<OneBody> up, dn;
    vector<TwoBody> upUp,upDn,dnDn;

    if( i== j ) up.push_back( {i, i, 1.0} );
    upDn.push_back( {i,j,j,i,-1.0} );

    applyOperatorsToWf(wf, wfNew, up, dn, upUp, upDn, dnDn);
}

void RealMaterial::applyNiNjToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew, size_t i, size_t j) const
{
    vector<OneBody> up, dn;
    vector<TwoBody> upUp,upDn,dnDn;

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
    vector<OneBody> up, dn;
    vector<TwoBody> upUp,upDn,dnDn;

    upDn.push_back( {i,j,i,j, 1.0} );
    applyOperatorsToWf(wf, wfNew, up, dn, upUp, upDn, dnDn);
}

void RealMaterial::applyCupiDaggerCupjToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew, size_t i, size_t j) const
{
    vector<OneBody> up, dn;
    vector<TwoBody> upUp,upDn,dnDn;

    up.push_back( {i,j, 1.0} );
    applyOperatorsToWf(wf, wfNew, up, dn, upUp, upDn, dnDn);
}

void RealMaterial::applyCdniDaggerCdnjToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew, size_t i, size_t j) const
{
    vector<OneBody> up, dn;
    vector<TwoBody> upUp,upDn,dnDn;

    dn.push_back( {i,j, 1.0} );
    applyOperatorsToWf(wf, wfNew, up, dn, upUp, upDn, dnDn);
}

void RealMaterial::applyOperatorsToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew,
                                      const vector<OneBody> &up, const vector<OneBody> &dn,
                                      const vector<TwoBody> &upUp, const vector<TwoBody> &upDn,
                                      const vector<TwoBody> &dnDn) const
{
    if( wfNew.size() != wf.size() ) wfNew.resize( wf.size() );
    const TensorHao<complex<double>, 1> & vec = wf.getWf();
    TensorHao<complex<double>, 1> & vecNew = wfNew.wfRef();

    size_t numUp, numDn, numNew;
    TableElement tableElementOne, tableElementTwo;

    #pragma omp parallel for private(numUp, numDn, numNew, tableElementOne, tableElementTwo)
    for(size_t num = 0; num < NHilbert; ++num)
    {
        vecNew(num) = 0;

        numDn = num/NHilbertUp;
        numUp = num -numDn*NHilbertUp;
        for( const OneBody& oneBody : up )
        {
            tableElementOne = tableUp( oneBody.j, oneBody.i, numUp );
            if( tableElementOne.coefficient != 0 )
            {
                numNew = tableElementOne.index + numDn * NHilbertUp;
                vecNew(num) += tableElementOne.coefficient * 1.0 * oneBody.K *  vec(numNew);
            }
        }

        for( const OneBody& oneBody : dn )
        {
            tableElementOne = tableDn( oneBody.j, oneBody.i, numDn );
            if( tableElementOne.coefficient != 0 )
            {
                numNew = numUp + tableElementOne.index * NHilbertUp;
                vecNew(num) += tableElementOne.coefficient * 1.0 * oneBody.K *  vec(numNew);
            }
        }

        for( const TwoBody& twoBody : upUp )
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

        for( const TwoBody& twoBody : upDn )
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

        for( const TwoBody& twoBody : dnDn )
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