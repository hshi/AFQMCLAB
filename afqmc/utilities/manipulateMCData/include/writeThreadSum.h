//
// Created by boruoshihao on 1/13/17.
//

#ifndef AFQMCLAB_WRITETHREADSUM_H
#define AFQMCLAB_WRITETHREADSUM_H

#include "../../../../common/tensorHao/include/tensor_all.h"
#include "../../../../common/readWriteHao/include/readWriteHao.h"

template<class T>
void writeThreadSum(T data, const std::string& filename, std::ios_base::openmode type= std::ios::trunc)
{
    T dataSum = MPISum(data);
    if( MPIRank()==0 ) writeFile(dataSum, filename, type);
}

template<class T>
void writeThreadSum(size_t L, const T *data, const std::string& filename, std::ios_base::openmode type= std::ios::trunc)
{
    std::vector<T> dataSum(L);
    MPISum( L, data, dataSum.data() );
    if( MPIRank()==0 ) writeFile(L, dataSum.data(), filename, type);
}

#endif //AFQMCLAB_WRITETHREADSUM_H
