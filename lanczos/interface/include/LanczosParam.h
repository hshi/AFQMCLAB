//
// Created by boruoshihao on 10/25/16.
//

#ifndef AFQMCLAB_LANCZOSPARAM_H
#define AFQMCLAB_LANCZOSPARAM_H

#include <cstddef>
#include <string>

class LanczosParam
{
 public:
    size_t matrixSize;        //Lanczos matrix size
    double accuracy;          //when new b smaller than accuracy, converge
    char convergeFlag;        //'E' or 'W', converge by wave function or energy
    size_t maxLoop;           //The max Lanczos matrix loop
    double litForProjection;  //When b is smaller, we need to project wave function.
    char lanwfsFlag;          //'R' or 'F', 'R' use recurse wf, 'F' store full Lanczos wf

    void read(const std::string& filename);
};

#endif //AFQMCLAB_LANCZOSPARAM_H