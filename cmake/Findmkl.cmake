set(HintLibraryPath "$ENV{MKL}/lib/intel64" "$ENV{MKLHOME}/lib/intel64" "$ENV{MKLROOT}/lib/intel64")
set(HintIncludePath "$ENV{MKL}/include" "$ENV{MKLHOME}/include" "$ENV{MKLROOT}/include")

set(mkl_definitions "")
set(mkl_flags "")

if(USE_INT64)
    set(mkl_definitions "-DMKL_ILP64" ${mkl_definitions})
    set(lpb4_name mkl_intel_ilp64)
else()
    set(lpb4_name mkl_intel_lp64)
endif()


if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(mkl_flags "-m64 ${mkl_flags}")
    if(USE_OPENMP)
        set(mkl_flags "-fopenmp ${mkl_flags}")
        set(sequential_name mkl_gnu_thread)
    else()
        set(sequential_name mkl_sequential)
    endif()
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    if(USE_OPENMP)
        set(mkl_flags "-qopenmp ${mkl_flags}")
        set(sequential_name mkl_intel_thread)
    else()
        set(sequential_name mkl_sequential)
    endif()
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "PGI")
    if(USE_OPENMP)
        set(mkl_flags " -mp -pgf90libs ${mkl_flags}")
        set(sequential_name mkl_pgi_thread)
    else()
        set(sequential_name mkl_sequential)
    endif()
endif()

#Set include directory
find_path(mkl_include_dirs mkl.h HINTS ${HintIncludePath})

#Set libraries
find_library(lp64_libraries NAMES ${lpb4_name} HINTS ${HintLibraryPath})
find_library(core_libraries NAMES mkl_core HINTS ${HintLibraryPath})
find_library(sequential_libraries NAMES ${sequential_name} HINTS ${HintLibraryPath})

set(mkl_libraries ${lp64_libraries} ${core_libraries} ${sequential_libraries} m dl pthread)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(mkl  DEFAULT_MSG
                                  mkl_libraries mkl_include_dirs)
mark_as_advanced(mkl_include_dirs mkl_libraries)

if(NOT MKL_FOUND)
  MESSAGE ("-- In order to find mkl, please define MKL or MKLHOME, MKL='/path/to/mkl' ")
endif()