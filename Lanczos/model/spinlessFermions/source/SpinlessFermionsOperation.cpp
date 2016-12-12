//
// Created by boruoshihao on 11/19/16.
//
#ifdef USE_OPENMP
#include <omp.h>
#endif

#include "../include/SpinlessFermions.h"
#include "../../../../libhao/mathHao/include/simple_fun.h"


using namespace std;
using namespace tensor_hao;

void SpinlessFermions::applyHToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew) const
{
    applyOperatorsToWf(wf, wfNew, K, V);
}

void SpinlessFermions::applyKToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew) const
{
    vector<LanTwoBody> V;
    applyOperatorsToWf(wf, wfNew, K, V);
}

void SpinlessFermions::applyVToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew) const
{
    vector<LanOneBody> K;
    applyOperatorsToWf(wf, wfNew, K, V);
}

void SpinlessFermions::applyNiNjToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew, size_t i, size_t j) const
{
    vector<LanOneBody> K;
    vector<LanTwoBody> V;

    V.push_back( {i, i, j, j, 1.0} );
    applyOperatorsToWf(wf, wfNew, K, V);
}

void SpinlessFermions::applyCiDaggerCjToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew, size_t i, size_t j) const
{
    vector<LanOneBody> K;
    vector<LanTwoBody> V;
    K.push_back( {i, j, 1.0} );

    applyOperatorsToWf(wf, wfNew, K, V);
}

void SpinlessFermions::applyOperatorsToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew,
                                          const std::vector<LanOneBody> &K,
                                          const std::vector<LanTwoBody> &V) const
{
    if( wfNew.size() != wf.size() ) wfNew.resize( wf.size() );
    const TensorHao<complex<double>, 1> & vec = wf.getWf();
    TensorHao<complex<double>, 1> & vecNew = wfNew.wfRef();

    #pragma omp parallel
    {
        #ifdef USE_OPENMP
        size_t threadRank = omp_get_thread_num();
        size_t threadSize = omp_get_num_threads();
        #else
        size_t threadRank = 0;
        size_t threadSize = 1;
        #endif

        size_t sizeEachThread = ( Nhilbert - 1 ) / threadSize + 1;
        size_t initIndex = sizeEachThread * threadRank;
        size_t endIndex = sizeEachThread * (threadRank + 1);

        if( initIndex > Nhilbert) initIndex = Nhilbert;
        if( endIndex > Nhilbert ) endIndex = Nhilbert;

        LanczosBasis lanBasis(L, N);
        if( initIndex < Nhilbert ) lanBasis.reSet( initIndex );

        TableElement tableElement;
        for(size_t num = initIndex; num < endIndex; ++num)
        {
            vecNew(num) = 0;

            for( const LanOneBody& oneBody : K )
            {
                tableElement = lanBasis.getInfoByCiDaggerCj(oneBody.j, oneBody.i);
                if( tableElement.coefficient != 0 )
                {
                    vecNew(num) += tableElement.coefficient * 1.0 * oneBody.K *  vec(tableElement.index);
                }
            }

            for( const LanTwoBody& twoBody : V )
            {
                tableElement = lanBasis.getInfoByCiDaggerCjCkDaggerCl(twoBody.l, twoBody.k, twoBody.j, twoBody.i);
                if( tableElement.coefficient != 0 )
                {
                    vecNew(num) += tableElement.coefficient * 1.0 * twoBody.V *  vec(tableElement.index);
                }
            }

            lanBasis.next();
        }

    }
}

void SpinlessFermions::applyCreationOperatorsToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew,
                                                  const std::vector<LanOneOperator> &C) const
{
    size_t NewHilbert = binomialCoeff(L, N+1);

    if( wfNew.size() != NewHilbert ) wfNew.resize( NewHilbert );
    const TensorHao<complex<double>, 1> & vec = wf.getWf();
    TensorHao<complex<double>, 1> & vecNew = wfNew.wfRef();

#pragma omp parallel
    {
#ifdef USE_OPENMP
        size_t threadRank = omp_get_thread_num();
        size_t threadSize = omp_get_num_threads();
#else
        size_t threadRank = 0;
        size_t threadSize = 1;
#endif

        size_t sizeEachThread = ( NewHilbert - 1 ) / threadSize + 1;
        size_t initIndex = sizeEachThread * threadRank;
        size_t endIndex = sizeEachThread * (threadRank + 1);

        if( initIndex > NewHilbert) initIndex = NewHilbert;
        if( endIndex > NewHilbert ) endIndex = NewHilbert;

        LanczosBasis lanBasis(L, N+1);
        if( initIndex < NewHilbert ) lanBasis.reSet( initIndex );

        LanczosBasis lanBasisPrime(L,N);
        TensorHao<size_t,1> positionOfParticlePrime(N);
        size_t destroyedParticle, numPrime;
        for(size_t num = initIndex; num < endIndex; ++num)
        {
            vecNew(num) = 0;

            for( const LanOneOperator& oneOperator : C )
            {
                const TensorHao<size_t,1> & positionOfParticle = lanBasis.getPositionOfParticle();

                destroyedParticle = N+1;
                for(size_t k = 0; k < (N + 1); ++k)
                {
                    if( oneOperator.i == positionOfParticle(k) ) { destroyedParticle = k; break; }
                }

                if( destroyedParticle != ( N+1 ) )
                {
                    for(size_t k = 0; k < destroyedParticle; ++k)
                        positionOfParticlePrime(k) = positionOfParticle(k);
                    for(size_t k = destroyedParticle+1; k < (N+1) ; ++k)
                        positionOfParticlePrime(k-1) = positionOfParticle(k);
                    numPrime = lanBasisPrime.getIndexFromPosition(positionOfParticlePrime);
                    vecNew(num) += pow(-1.0, destroyedParticle) * oneOperator.C * vec( numPrime ) ;
                }
            }

            lanBasis.next();
        }
    }
}

void SpinlessFermions::applyAnnihilationOperatorsToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew,
                                                      const std::vector<LanOneOperator> &C) const
{
    size_t NewHilbert = binomialCoeff(L, N-1);

    if( wfNew.size() != NewHilbert ) wfNew.resize( NewHilbert );
    const TensorHao<complex<double>, 1> & vec = wf.getWf();
    TensorHao<complex<double>, 1> & vecNew = wfNew.wfRef();

#pragma omp parallel
    {
#ifdef USE_OPENMP
        size_t threadRank = omp_get_thread_num();
        size_t threadSize = omp_get_num_threads();
#else
        size_t threadRank = 0;
        size_t threadSize = 1;
#endif

        size_t sizeEachThread = ( NewHilbert - 1 ) / threadSize + 1;
        size_t initIndex = sizeEachThread * threadRank;
        size_t endIndex = sizeEachThread * (threadRank + 1);

        if( initIndex > NewHilbert) initIndex = NewHilbert;
        if( endIndex > NewHilbert ) endIndex = NewHilbert;

        LanczosBasis lanBasis(L, N-1);
        if( initIndex < NewHilbert ) lanBasis.reSet( initIndex );

        LanczosBasis lanBasisPrime(L,N);
        TensorHao<size_t,1> positionOfParticlePrime(N);
        size_t createdParticle, numPrime, existFlag;
        for(size_t num = initIndex; num < endIndex; ++num)
        {
            vecNew(num) = 0;

            for( const LanOneOperator& oneOperator : C )
            {
                const TensorHao<size_t,1> & positionOfParticle = lanBasis.getPositionOfParticle();

                existFlag = 0;
                for(size_t k = 0; k < (N - 1); ++k)
                {
                    if( oneOperator.i == positionOfParticle(k) ) { existFlag = 1; break; }
                }

                if( existFlag == 0 )
                {
                    createdParticle = N-1;
                    for(size_t k = 0; k < (N - 1); ++k)
                    {
                        if( oneOperator.i < positionOfParticle(k) ) { createdParticle = k; break; }
                    }

                    positionOfParticlePrime(createdParticle) = oneOperator.i;
                    for(size_t k = 0; k < createdParticle; ++k)
                        positionOfParticlePrime(k) = positionOfParticle(k);
                    for(size_t k = createdParticle+1; k < N ; ++k)
                        positionOfParticlePrime(k) = positionOfParticle(k-1);

                    numPrime = lanBasisPrime.getIndexFromPosition(positionOfParticlePrime);

                    vecNew(num) += pow(-1.0, createdParticle) * oneOperator.C * vec( numPrime ) ;
                }

            }

            lanBasis.next();
        }
    }
}