//
// Created by boruoshihao on 4/10/17.
//

#ifndef AFQMCLAB_MEASUREDYNAMICPARAM_H
#define AFQMCLAB_MEASUREDYNAMICPARAM_H

struct DynamicParams
{
    size_t matrixSize;        //Lanczos matrix size
    double accuracy;          //when new b smaller than accuracy, converge
    double litForProjection;  //When b is smaller, we need to project wave function.
    char lanwfsFlag;          //'R' or 'F', 'R' use recurse wf, 'F' store full Lanczos wf
};

#endif //AFQMCLAB_MEASUREDYNAMICPARAM_H
