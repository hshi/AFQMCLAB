//
// Created by boruoshihao on 7/30/17.
//

#ifndef AFQMCLAB_TENSOR_MYABS_H
#define AFQMCLAB_TENSOR_MYABS_H

#include <complex>

template <class T> T myabs(std::complex<T> a)
{
    return std::abs(a);
}

template <class T> T myabs(T a)
{
    if( a>0 ) return a;
    else return -a;
}

#endif //AFQMCLAB_TENSOR_MYABS_H
