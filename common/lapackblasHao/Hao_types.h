//
// Created by boruoshihao on 10/1/16.
//

#ifndef AFQMCLAB_DATA_TYPES_H
#define AFQMCLAB_DATA_TYPES_H

#ifdef __cplusplus
    extern "C" {
#endif /* __cplusplus */

/* HAO Complex type for single precision */
#ifndef HAO_Complex8

    typedef
    struct _HAO_Complex8 {
        float real;
        float imag;
    } HAO_Complex8;

#endif

/* HAO Complex type for double precision */
#ifndef HAO_Complex16

    typedef
    struct _HAO_Complex16 {
        double real;
        double imag;
    } HAO_Complex16;

#endif

/* HAO integer types for LP64 and ILP64 */
#if (!defined(__INTEL_COMPILER)) & defined(_MSC_VER)

    #define HAO_INT64 __int64
    #define HAO_UINT64 unsigned __int64

#else

    #define HAO_INT64 long long int
    #define HAO_UINT64 unsigned long long int

#endif

#ifdef USE_INT64

    /* HAO ILP64 integer types */
    #ifndef HAO_INT
        #define HAO_INT HAO_INT64
    #endif

    #ifndef HAO_UINT
        #define HAO_UINT HAO_UINT64
    #endif

    #define HAO_LONG HAO_INT64

#else

     /* HAO LP64 integer types */
     #ifndef HAO_INT
         #define HAO_INT int
     #endif

     #ifndef HAO_UINT
         #define HAO_UINT unsigned int
     #endif

     #define HAO_LONG long int

#endif

#ifdef __cplusplus
    }
#endif /* __cplusplus */

#endif //AFQMCLAB_DATA_TYPES_H