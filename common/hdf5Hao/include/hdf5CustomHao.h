//
// Created by boruoshihao on 5/30/17.
//
#ifndef AFQMCLAB_HDF5CUSTOMHAO_H
#define AFQMCLAB_HDF5CUSTOMHAO_H

#include <iostream>
#include <complex>
#include "H5Cpp.h"

namespace H5
{
    template<typename... Values>
    DataSpace returnDataspace(hsize_t input, Values... inputs)
    {
        size_t len = sizeof...(Values) + 1;
        hsize_t vals[] = {input, static_cast<hsize_t>(inputs)...};
        return DataSpace(len, vals);
    }

    CompType returnComplexDoubleCompType(const PredType &predType);

    size_t returnDataSetSize(const DataSet &dataset);
}

#endif //AFQMCLAB_HDF5CUSTOMHAO_H