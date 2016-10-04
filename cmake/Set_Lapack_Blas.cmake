set(findlapackblas off)

#Check mkl
if(NOT findlapackblas)
    find_package(mkl)
    if(MKL_FOUND)
        message("-- Use MKL library." )
        set(findlapackblas on)
        set(lapackblas_definitions "-DUSE_MKL" ${mkl_definitions})
        set(lapackblas_flags ${mkl_flags})
        set(lapackblas_include_dirs ${mkl_include_dirs})
        set(lapackblas_libraries "${mkl_libraries}")
    endif()
endif()

#Check acml
if(NOT findlapackblas)
    find_package(acml)
    if(ACML_FOUND)
        message("-- Use ACML library." )
        set(findlapackblas on)
        set(lapackblas_definitions "-DUSE_ACML")
        set(lapackblas_flags "")
        set(lapackblas_include_dirs ${acml_include_dirs})
        set(lapackblas_libraries "${acml_libraries}")
    endif()
endif()

if(NOT findlapackblas)
    find_package(LAPACK)
    if(LAPACK_FOUND AND BLAS_FOUND)
        message("-- Use system lapack and blas library." )
        if(USE_OPENMP)
            message("-- WARNING!!! System lapack and blas does not support openmp.")
        endif()
        set(findlapackblas on)
        set(lapackblas_definitions "-DUSE_BLAS_LAPACK")
        set(lapackblas_flags "")
        set(lapackblas_include_dirs "")
        set(lapackblas_libraries ${LAPACK_LIBRARIES})
    endif()
endif()

if(NOT findlapackblas)
    message( FATAL_ERROR "Find no library for blas and lapack!" )
endif()

#Usually, Fortran has underscore
#No need to turn on FORTRAN_NO_UNDERSCORE
if(FORTRAN_NO_UNDERSCORE)
    set(lapackblas_definitions "-DDFORTRAN_NO_UNDERSCORE" "${lapackblas_definitions}")
endif()

#For magma library
if(USE_MAGMA)
    message("-- Use MAGMA library." )
    # Use standard FindCUD
    find_package(CUDA REQUIRED)
    find_package(magma REQUIRED)
    set(lapackblas_definitions ${lapackblas_definitions} "-DUSE_MAGMA")
    set(lapackblas_include_dirs ${lapackblas_include_dirs} ${magma_include_dirs} ${CUDA_INCLUDE_DIRS})
    set(lapackblas_libraries ${lapackblas_libraries} "${magma_libraries}" ${CUDA_LIBRARIES} ${CUDA_CUBLAS_LIBRARIES})
else()
    MESSAGE("-- MAGMA support was disabled.")
endif()

list(REMOVE_DUPLICATES lapackblas_libraries)