//
// Created by boruoshihao on 5/30/17.
//
#include "../include/hdf5CustomHao.h"

using namespace std;
using namespace H5;

namespace H5
{
    CompType returnComplexDoubleCompType(const PredType &predType)
    {
        typedef struct
        {
            double  a;
            double  b;
        } tmpType;

        CompType complexDoubleCompType( sizeof(tmpType)  );
        complexDoubleCompType.insertMember( "real", HOFFSET(tmpType, a), predType);
        complexDoubleCompType.insertMember( "imag", HOFFSET(tmpType, b), predType);
        return complexDoubleCompType;
    }

    size_t returnDataSetSize(const DataSet &dataset)
    {
        DataSpace dataSpace= dataset.getSpace();
        size_t D = dataSpace.getSimpleExtentNdims();
        hsize_t n[D]; dataSpace.getSimpleExtentDims(n);
        size_t dataSize=1; for(size_t i = 0; i < D; ++i) dataSize *= n[i];
        return dataSize;
    }
}