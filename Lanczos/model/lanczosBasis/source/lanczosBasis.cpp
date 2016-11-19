//
// Created by boruoshihao on 10/28/16.
//
#include <algorithm>
#include <iostream>
#include "../include/lanczosBasis.h"

using namespace std;

using namespace tensor_hao;

LanczosBasis::LanczosBasis(size_t L, size_t N) : sizeOfBasis(L), numberOfParticle(N)
{
    setPositions();
    setBinomialTable();
    init();
}

size_t LanczosBasis::getSizeOfBasis() const { return sizeOfBasis; }

size_t LanczosBasis::getNumberOfParticle() const { return numberOfParticle; }

size_t LanczosBasis::getIndex() const { return index; }

const TensorHao<size_t,1> &LanczosBasis::getPositionOfParticle() const { return positionOfParticle; }

const TensorHao<size_t, 1> &LanczosBasis::getEmptyPositionForParticle() const { return emptyPositionForParticle; }

const TensorHao<size_t,2> &LanczosBasis::getBinomialTable() const { return binomialTable; }

void LanczosBasis::init()
{
    index = 0;
    for(size_t i = 0; i < numberOfParticle; ++i)
    {
        positionOfParticle(i) = i;
        emptyPositionForParticle(i) = 0;
    }
    emptyPositionForParticle(numberOfParticle-1) = sizeOfBasis - numberOfParticle;
}

void LanczosBasis::reSet(size_t index)
{
    LanczosBasis::index = index;

    for(int positionIndex = sizeOfBasis-1; positionIndex > -1 ; --positionIndex)
    {
       if( binomialTable( positionIndex, numberOfParticle ) <= index )
       {
           index -= binomialTable( positionIndex, numberOfParticle );
           positionOfParticle( numberOfParticle-1 ) = positionIndex;
           emptyPositionForParticle( numberOfParticle-1 ) = sizeOfBasis - positionIndex - 1;
           break;
       }
    }

    for(int particleIndex = numberOfParticle-2; particleIndex > -1 ; --particleIndex)
    {
        for(int positionIndex = positionOfParticle(particleIndex+1)-1; positionIndex > -1 ; --positionIndex)
        {
            if( binomialTable( positionIndex, particleIndex+1 ) <= index )
            {
                index -= binomialTable( positionIndex, particleIndex+1 );
                positionOfParticle( particleIndex ) = positionIndex;
                emptyPositionForParticle( particleIndex ) = positionOfParticle(particleIndex+1) - positionIndex - 1;
                break;
            }
        }
    }

    if(index != 0 ) { cout<<"Error!!! Index is not zero after get positions!"<<endl; exit(1); }
}

int LanczosBasis::next()
{
    for(size_t i = 0; i < numberOfParticle; ++i)
    {
        if( emptyPositionForParticle(i) > 0 )
        {
            index++;
            positionOfParticle(i)++;
            emptyPositionForParticle(i)--;
            if( i>0 )
            {
                if( positionOfParticle(0) == 0 )
                {
                    emptyPositionForParticle(i-1)++;
                }
                else
                {
                    for(size_t j = 0; j < i; ++j)
                    {
                        positionOfParticle(j) = j;
                        emptyPositionForParticle(j) = 0;
                    }
                    emptyPositionForParticle(i-1) = positionOfParticle(i) - positionOfParticle(i-1) - 1;
                }
            }
            return 0;
        }
    }
    return 1;
}

size_t LanczosBasis::getIndexFromPosition(const TensorHao<size_t,1> &position)
{
    size_t count = 0;
    for(size_t i = 0; i < numberOfParticle ; ++i)
    {
        count += binomialTable( positionOfParticle(i), i+1 );
    }
    return count;
}

TableElement LanczosBasis::getInfoByCiDaggerCj(size_t i, size_t j)
{
    if( i == j )
    {
        for(size_t k = 0; k < numberOfParticle; ++k)  { if( positionOfParticle(k) == i ) return {index, 1}; }
        return {index, 0};
    }

    for(size_t k = 0; k < numberOfParticle; ++k) { if( positionOfParticle(k) == i ) return {index, 0}; }

    size_t destroyedParticle(numberOfParticle);
    for(size_t k = 0; k < numberOfParticle; ++k)
    {
        if( positionOfParticle(k) == j )
        {
            destroyedParticle = k;
            break;
        }
    }
    if( destroyedParticle == numberOfParticle ) return {index, 0};

    int coe(1); size_t indexNew(index); size_t createdParticle;

    if( i> j )
    {
        indexNew -= binomialTable(positionOfParticle(destroyedParticle), destroyedParticle+1);
        for(createdParticle = destroyedParticle + 1; createdParticle < numberOfParticle; ++createdParticle)
        {
            if( positionOfParticle(createdParticle) < i )
            {
                coe *= (-1);
                indexNew -= binomialTable( positionOfParticle(createdParticle), createdParticle+1 );
                indexNew += binomialTable( positionOfParticle(createdParticle), createdParticle );
            }
            else
            {
                break;
            }
        }
        indexNew += binomialTable( i, createdParticle );
        return {indexNew, coe};
    }
    else if( i< j )
    {
        indexNew -= binomialTable(positionOfParticle(destroyedParticle), destroyedParticle+1);
        for(createdParticle = destroyedParticle; createdParticle >0; --createdParticle)
        {
            if( positionOfParticle(createdParticle-1) > i )
            {
                coe *= (-1);
                indexNew -= binomialTable( positionOfParticle(createdParticle-1), createdParticle );
                indexNew += binomialTable( positionOfParticle(createdParticle-1), createdParticle+1 );
            }
            else
            {
                break;
            }
        }
        indexNew += binomialTable( i, createdParticle+1 );
        return {indexNew, coe};
    }
    else
    {
        cout<<"Error!!! We should not reach here!"<<endl; exit(1);
    }
}

void LanczosBasis::setPositions()
{
    positionOfParticle.resize( numberOfParticle );
    emptyPositionForParticle.resize( numberOfParticle );
    tempPositionOfParticle.resize( numberOfParticle );
}

void LanczosBasis::setBinomialTable()
{
    binomialTable.resize( sizeOfBasis+1, numberOfParticle+1 );

    for(size_t j = 0; j <= sizeOfBasis; j++)
    {
        for(size_t i = 0; i <= numberOfParticle; i++)
        {
            if ( i>j ) binomialTable(j,i)=0;
            else if (i == 0 || i == j) binomialTable(j, i) =1;
            else binomialTable(j,i) = binomialTable(j-1, i-1) + binomialTable(j-1,i);
        }
    }
}

LanczosBasis::LanczosBasis(const LanczosBasis &x) {}
LanczosBasis &LanczosBasis::operator=(const LanczosBasis &x) { return *this; }