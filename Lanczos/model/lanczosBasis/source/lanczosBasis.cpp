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

void LanczosBasis::reSet(size_t index)
{
    LanczosBasis::index = index;

    int lastPosition = sizeOfBasis;
    for(int particleIndex = numberOfParticle-1; particleIndex > -1 ; --particleIndex)
    {
        for(int positionIndex = lastPosition-1; positionIndex > -1 ; --positionIndex)
        {
            if( binomialTable( positionIndex, particleIndex+1 ) <= index )
            {
                positionOfParticle( particleIndex ) = positionIndex;
                emptyPositionForParticle( particleIndex ) = lastPosition - positionIndex - 1;

                index -= binomialTable( positionIndex, particleIndex+1 );
                lastPosition = positionIndex;

                break;
            }
        }
    }

    if(index != 0 ) { cout<<"Error!!! Index is not zero after get positions!"<<endl; exit(1); }
}

size_t LanczosBasis::getIndexFromPosition(const TensorHao<size_t,1> &position)
{
    size_t count = 0;
    for(size_t i = 0; i < numberOfParticle ; ++i)
    {
        count += binomialTable( position(i), i+1 );
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

    int coe; size_t indexNew(index); size_t createdParticle;

    if( i> j )
    {
        indexNew -= binomialTable(positionOfParticle(destroyedParticle), destroyedParticle+1);
        for(createdParticle = destroyedParticle + 1; createdParticle < numberOfParticle; ++createdParticle)
        {
            if( positionOfParticle(createdParticle) < i )
            {
                indexNew -= binomialTable( positionOfParticle(createdParticle), createdParticle+1 );
                indexNew += binomialTable( positionOfParticle(createdParticle), createdParticle );
            }
            else
            {
                break;
            }
        }
        indexNew += binomialTable( i, createdParticle );
        coe = createdParticle - destroyedParticle - 1;
        coe = pow(-1, coe);
        return {indexNew, coe};
    }
    else if( i< j )
    {
        indexNew -= binomialTable(positionOfParticle(destroyedParticle), destroyedParticle+1);
        for(createdParticle = destroyedParticle; createdParticle >0; --createdParticle)
        {
            if( positionOfParticle(createdParticle-1) > i )
            {
                indexNew -= binomialTable( positionOfParticle(createdParticle-1), createdParticle );
                indexNew += binomialTable( positionOfParticle(createdParticle-1), createdParticle+1 );
            }
            else
            {
                break;
            }
        }
        indexNew += binomialTable( i, createdParticle+1 );
        coe = destroyedParticle - createdParticle;
        coe = pow(-1, coe);
        return {indexNew, coe};
    }
    else
    {
        cout<<"Error!!! We should not reach here!"<<endl; exit(1);
    }
}

TableElement LanczosBasis::getInfoByCiDaggerCjCkDaggerCl(size_t i, size_t j, size_t k, size_t l)
{
    // CiDaggerCj nk
    if( k == l )
    {
        for(size_t m = 0; m < numberOfParticle; ++m)
        {
            if( positionOfParticle(m) == k ) return getInfoByCiDaggerCj(i, j);
        }
        return {index, 0};
    }

    // k != l
    // CiDaggerCl CkCkDagger
    if( j == k )
    {
        for(size_t m = 0; m < numberOfParticle; ++m)
        {
            if( positionOfParticle(m) == k ) return {index, 0};
        }
        return getInfoByCiDaggerCj(i, l);
    }

    // k != l , k != j
    //-CiDaggerCkDagger CjCl
    if( j == l ) return {index, 0};
    if( i == k ) return {index, 0};

    // k != l, k != j, k != i, j != l
    // CkDaggerCl ni
    if( i == j )
    {
        for(size_t m = 0; m < numberOfParticle; ++m)
        {
            if( positionOfParticle(m) == i ) return getInfoByCiDaggerCj(k, l);
        }
        return {index, 0};
    }

    // k != l, k != j, k != i, j != l, j != i
    // -CkDaggerCj ni
    if( i == l )
    {
        for(size_t m = 0; m < numberOfParticle; ++m)
        {
            if( positionOfParticle(m) == i )
            {
                TableElement element = getInfoByCiDaggerCj(k, j);
                element.coefficient *= -1;
                return element;
            }
        }
        return {index, 0};
    }

    // k != l, k != j, k != i, j != l, j != i, i != l
    // Apply Twice to get new TableElement
    // CiDaggerCj CkDaggerCl
    tempPositionOfParticle = positionOfParticle;
    int coe = applyCiDaggerCj(k, l, tempPositionOfParticle);
    if(coe == 0 ) return {index, 0};

    coe *= applyCiDaggerCj(i, j, tempPositionOfParticle);
    if(coe == 0 ) return {index, 0};

    size_t num = getIndexFromPosition( tempPositionOfParticle );
    return {num, coe};
}

TableElement LanczosBasis::getInfoByCi(size_t i)
{
    size_t destroyedParticle(numberOfParticle);
    for(size_t k = 0; k < numberOfParticle; ++k)
    {
        if( positionOfParticle(k) == i ) { destroyedParticle = k; break; }
    }
    if( destroyedParticle == numberOfParticle ) return {0, 0};

    int coe = destroyedParticle; coe = pow(-1, coe);

    size_t count = 0;
    for(size_t k = 0; k < destroyedParticle; ++k)
    {
        count += binomialTable( positionOfParticle(k), k+1 );
    }
    for(size_t k = destroyedParticle+1; k < numberOfParticle ; ++k)
    {
        count += binomialTable( positionOfParticle(k), k );
    }

    return {count, coe};
}


TableElement LanczosBasis::getInfoByCiDagger(size_t i)
{
    for(size_t k = 0; k < numberOfParticle; ++k) { if( positionOfParticle(k) == i ) return {0, 0}; }

    size_t createdParticle = numberOfParticle;
    for(size_t k = 0; k < numberOfParticle; ++k)
    {
        if( i < positionOfParticle(k) ) { createdParticle = k; break; }
    }

    int coe = createdParticle; coe = pow(-1, coe);

    size_t count = 0;
    for(size_t k = 0; k < createdParticle ; ++k)
    {
        count += binomialTable( positionOfParticle(k), k+1 );
    }
    count += binomialTable(i, createdParticle+1);
    for(size_t k = createdParticle; k < numberOfParticle ; ++k)
    {
        count += binomialTable( positionOfParticle(k), k+2 );
    }

    return {count, coe};
}

void LanczosBasis::setPositions()
{
    positionOfParticle.resize( numberOfParticle );
    emptyPositionForParticle.resize( numberOfParticle );
    tempPositionOfParticle.resize( numberOfParticle );
}

void LanczosBasis::setBinomialTable()
{
    binomialTable.resize( sizeOfBasis+1, numberOfParticle+2 );

    for(size_t j = 0; j < sizeOfBasis+1; j++)
    {
        for(size_t i = 0; i < numberOfParticle+2; i++)
        {
            if ( i>j ) binomialTable(j,i)=0;
            else if (i == 0 || i == j) binomialTable(j, i) =1;
            else binomialTable(j,i) = binomialTable(j-1, i-1) + binomialTable(j-1,i);
        }
    }
}

int LanczosBasis::applyCiDaggerCj(size_t i, size_t j, TensorHao<size_t, 1> &positionInOut)
{
    if( i == j )
    {
        for(size_t k = 0; k < numberOfParticle; ++k)  { if( positionInOut(k) == i ) return 1; }
        return 0;
    }

    for(size_t k = 0; k < numberOfParticle; ++k) { if( positionInOut(k) == i ) return 0; }

    size_t destroyedParticle(numberOfParticle);
    for(size_t k = 0; k < numberOfParticle; ++k)
    {
        if( positionInOut(k) == j )
        {
            destroyedParticle = k;
            break;
        }
    }
    if( destroyedParticle == numberOfParticle ) return 0;

    int exchangeNumber; size_t createdParticle;
    if( i> j )
    {
        for(createdParticle = destroyedParticle + 1; createdParticle < numberOfParticle; ++createdParticle)
        {
            if( positionInOut(createdParticle) < i )
            {
                positionInOut(createdParticle-1) = positionInOut(createdParticle);
            }
            else
            {
                break;
            }
        }
        positionInOut(createdParticle-1) = i;
        exchangeNumber = createdParticle - destroyedParticle - 1;
    }
    else if( i< j )
    {
        for(createdParticle = destroyedParticle; createdParticle >0; --createdParticle)
        {
            if( positionInOut(createdParticle-1) > i )
            {
                positionInOut(createdParticle) = positionInOut(createdParticle-1);
            }
            else
            {
                break;
            }
        }
        positionInOut(createdParticle) = i;
        exchangeNumber = destroyedParticle - createdParticle;
    }
    else
    {
        cout<<"Error!!! We should not reach here!"<<endl; exit(1);
    }
    return pow(-1, exchangeNumber);
}

LanczosBasis::LanczosBasis(const LanczosBasis &x) {}
LanczosBasis &LanczosBasis::operator=(const LanczosBasis &x) { return *this; }