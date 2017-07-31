#ifndef TENSOR_HAO_LIBRARY_ALL_H
#define TENSOR_HAO_LIBRARY_ALL_H

#include "readWriteTemplateForTensor.h"
#include "tensor_core.h"
#include "tensor_hao_ref.h"
#include "tensor_hao.h"
#include "tensor_element_wise.h"
#include "tensor_mpi.h"
#include "tensor_fill.h"
#include "tensor_1d_bl_cpu.h"
#include "tensor_2d_common_fun.h"
#include "tensor_2d_bl_cpu.h"
#include "tensor_2d_bl_magma.h"
#include "tensor_myabs.h"

#ifdef USE_MAGMA
   #define BL_NAME(x) x##_magma
#else
   #define BL_NAME(x) x##_cpu
#endif

#endif

