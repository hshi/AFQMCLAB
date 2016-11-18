//
// Created by boruoshihao on 10/28/16.
//
#include <algorithm>
#include <iostream>
#include "../include/lanczosBasis.h"

using namespace std;

LanczosBasis::LanczosBasis(size_t L, size_t N) : sizeOfBasis(L), numberOfParticle(N)
{
    linkStackOrHeap();
    setBinomialTable();
    init();
}

size_t LanczosBasis::getSizeOfBasis() const { return sizeOfBasis; }

size_t LanczosBasis::getNumberOfParticle() const { return numberOfParticle; }

const size_t *LanczosBasis::getPositionOfParticle() const { return positionOfParticle; }

void LanczosBasis::init()
{
    index = 0;
    for(size_t i = 0; i < numberOfParticle; ++i)
    {
        positionOfParticle[i] = i;
        emptyPositionForParticle[i] = 0;
    }
    emptyPositionForParticle[numberOfParticle-1] = sizeOfBasis - numberOfParticle;
}

int LanczosBasis::next()
{
    for(size_t i = 0; i < numberOfParticle; ++i)
    {
        if( emptyPositionForParticle[i] > 0 )
        {
            index++;
            positionOfParticle[i]++;
            emptyPositionForParticle[i]--;

            if( i>0 )
            {
                if( positionOfParticle[0] == 0 )
                {
                    emptyPositionForParticle[i-1]++;
                }
                else
                {
                    for(size_t j = 0; j < i; ++j)
                    {
                        positionOfParticle[j] = j;
                        emptyPositionForParticle[j] = 0;
                    }
                    emptyPositionForParticle[i-1] = positionOfParticle[i] - positionOfParticle[i-1] - 1;
                }
            }
            return 0;
        }
    }
    return 1;
}

size_t LanczosBasis::getIndexFromPosition(const size_t *position)
{
    size_t count = 0;
    for(size_t i = 0; i < numberOfParticle ; ++i)
    {
        count += binomial(positionOfParticle[i], i+1);
    }
    return count;
}

TableElement LanczosBasis::getInfoByCiDaggerCj(size_t i, size_t j)
{
    if( i == j )
    {
        for(size_t k = 0; k < numberOfParticle; ++k)  { if( positionOfParticle[k] == i ) return {index, 1}; }
        return {index, 0};
    }

    for(size_t k = 0; k < numberOfParticle; ++k) { if( positionOfParticle[k] == i ) return {index, 0}; }

    size_t destroyedParticle(numberOfParticle);
    for(size_t k = 0; k < numberOfParticle; ++k)
    {
        if( positionOfParticle[k] == j )
        {
            destroyedParticle = k;
            break;
        }
    }
    if( destroyedParticle == numberOfParticle ) return {index, 0};

    int coe(1); size_t indexNew(index); size_t createdParticle;

    if( i> j )
    {
        indexNew -= binomial(positionOfParticle[destroyedParticle], destroyedParticle+1);
        for(createdParticle = destroyedParticle + 1; createdParticle < numberOfParticle; ++createdParticle)
        {
            if( positionOfParticle[createdParticle] < i )
            {
                coe *= (-1);
                indexNew -= binomial( positionOfParticle[createdParticle], createdParticle+1 );
                indexNew += binomial( positionOfParticle[createdParticle], createdParticle );
            }
            else
            {
                break;
            }
        }
        indexNew += binomial( i, createdParticle );
        return {indexNew, coe};
    }
    else if( i< j )
    {
        indexNew -= binomial(positionOfParticle[destroyedParticle], destroyedParticle+1);
        for(createdParticle = destroyedParticle; createdParticle >0; --createdParticle)
        {
            if( positionOfParticle[createdParticle-1] > i )
            {
                coe *= (-1);
                indexNew -= binomial( positionOfParticle[createdParticle-1], createdParticle );
                indexNew += binomial( positionOfParticle[createdParticle-1], createdParticle+1 );
            }
            else
            {
                break;
            }
        }
        indexNew += binomial( i, createdParticle+1 );
        return {indexNew, coe};
    }
    else
    {
        cout<<"Warning!!! We should not reach here!"<<endl; exit(1);
    }
}

void LanczosBasis::linkStackOrHeap()
{
    if( numberOfParticle > maxParticleInStack )
    {
        positionOfParticleHeap.resize( numberOfParticle );
        emptyPositionForParticleHeap.resize( numberOfParticle );
        tempPositionOfParticleHeap.resize( numberOfParticle );

        positionOfParticle = positionOfParticleHeap.data();
        emptyPositionForParticle = emptyPositionForParticleHeap.data();
        tempPositionOfParticle = tempPositionOfParticleHeap.data();
    }
    else
    {
        positionOfParticle = positionOfParticleStack;
        emptyPositionForParticle = emptyPositionForParticleStack;
        tempPositionOfParticle = tempPositionOfParticleStack;
    }

    if( (sizeOfBasis+1)*(numberOfParticle+1) > maxBinomialInStack )
    {
        binomialTableHeap.resize( (sizeOfBasis+1)*(numberOfParticle+1) );
        binomialTable = binomialTableHeap.data();
    }
    else
    {
        binomialTable = binomialTableStack;
    }
}

void LanczosBasis::setBinomialTable()
{
    for(size_t j = 0; j <= sizeOfBasis; j++)
    {
        for(size_t i = 0; i <= numberOfParticle; i++)
        {
            if ( i>j ) binomial(j,i)=0;
            else if (i == 0 || i == j) binomial(j, i) =1;
            else binomial(j,i) = binomial(j-1, i-1) + binomial(j-1,i);
        }
    }
}

LanczosBasis::LanczosBasis(const LanczosBasis &x) {}
LanczosBasis &LanczosBasis::operator=(const LanczosBasis &x) { return *this; }