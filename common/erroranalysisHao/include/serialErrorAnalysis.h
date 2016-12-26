#ifndef AFQMCLAB_SERIAL_ERROR_ANALYSIS_H
#define AFQMCLAB_SERIAL_ERROR_ANALYSIS_H

#include <iostream>
#include <vector>
#include <complex>
#include <typeinfo>
#include <tuple>
#include "kahan.h"

std::vector<size_t> getDivisors(const size_t n);

template<class T>  std::vector<T> setBlockVector(const size_t L, const size_t blk_size, const T *array);

//=====================================================================================
//For pointer: getMean, getError, getMeanError, getBlockMeanError, getAllBlockMeanError
//=====================================================================================
template<class T> T getMean(const size_t L, const T *array)
{
    KahanData<T> ksum;
    for(size_t i=0; i<L; i++) ksum+=array[i];
    return ksum.returnSum()/static_cast<T>(L);
}

template<class T> T getVariance(const size_t L, const T *array, const T &mean)
{
    KahanData<T> ksum;
    for(size_t i=0; i<L; i++) ksum+=std::norm(array[i]-mean);

    T variance=ksum.returnSum()/static_cast<T>(L);
    return variance;
}

template<class T> T getError(const size_t L, const T *array, const T &mean)
{
    if(L==1) {return 0;}
    T variance= getVariance(L, array, mean);
    return sqrt(variance/static_cast<T>(L-1));
}

template<class T> std::tuple <T,T> getMeanError(const size_t L, const T *array)
{
    T mean = getMean(L, array);
    T err  = getError(L, array, mean);
    return std::make_tuple(mean, err);
}

template<class T> std::tuple <T,T> getBlockMeanError(const size_t L, const size_t blk_size, const T *array)
{
    if( L%blk_size!=0 ) std::cerr<<"Warning!!!!!! L can not be divided by blk_size!"<<std::endl;

    std::vector<T> blockVector = setBlockVector(L, blk_size, array);

    return getMeanError( blockVector.size(), blockVector.data() );
}

template<class T> std::tuple<  std::vector<size_t>, std::vector<T>, std::vector<T> >
getAllBlockMeanError(const size_t L, const T *array)
{
    std::vector<size_t> divisors = getDivisors(L);
    std::vector<T> mean( divisors.size() );
    std::vector<T> err( divisors.size() );
    for(size_t i=0; i<divisors.size(); i++)
    {
        std::tie( mean[i], err[i] ) = getBlockMeanError(L, divisors[i], array);
    }
    return std::make_tuple( std::move(divisors),  std::move(mean), std::move(err) );
}


//====================================================================================
//For vector: getMean, getError, getMeanError, getBlockMeanError, getAllBlockMeanError
//====================================================================================
template<class T> T getMean(const std::vector<T> &vec)
{
    size_t  L=vec.size();
    return getMean( L, vec.data() );
}

template<class T> T getVariance(const std::vector<T> &vec, const T &mean)
{
    size_t  L=vec.size();
    return  getVariance(L, vec.data(), mean);
}

template<class T> T getError(const std::vector<T> &vec, const T &mean)
{
    size_t  L=vec.size();
    return  getError(L, vec.data(), mean);
}

template<class T> std::tuple <T,T> getMeanError(const std::vector<T> &vec)
{
    size_t L=vec.size();
    return getMeanError( L, vec.data() );
}

template<class T> std::tuple <T,T> getBlockMeanError(const size_t blk_size, const std::vector<T> &vec)
{
    size_t  L=vec.size();
    return getBlockMeanError( L, blk_size, vec.data() );
}

template<class T> std::tuple<  std::vector<size_t>, std::vector<T>, std::vector<T> >
getAllBlockMeanError (const std::vector<T> &vec )
{
    size_t L=vec.size();
    return getAllBlockMeanError( L, vec.data() );
}


//====================
//Supplyment functions
//====================
template<class T>  std::vector<T> setBlockVector(const size_t L, const size_t blk_size, const T *array)
{
    size_t blk_num= L/blk_size;
    std::vector<T> blockVector( blk_num );

    const T* oneBlockArray=array;
    for(size_t i=0; i<blk_num; i++)
    {
        blockVector[i]=getMean(blk_size, oneBlockArray);
        oneBlockArray+=blk_size;
    }
    return blockVector;
}

#endif
