cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(AFQMCLAB C CXX)

set(AFQMCLAB_MAJOR_VERSION 0)
set(AFQMCLAB_MINOR_VERSION 1)
set(AFQMCLAB_PATCH_VERSION 0)
set(AFQMCLAB_VERSION ${AFQMCLAB_MAJOR_VERSION}.${AFQMCLAB_MINOR_VERSION}.${AFQMCLAB_PATCH_VERSION})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

set(PLATFORM "DEFUALT" CACHE STRING "The platform to be run.")
include("PLATFORM_${PLATFORM}")
message("-- Using the compiler ${CMAKE_CXX_COMPILER_ID}")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

include(FUNCTION_CUSTOM)

#Set librarys
find_package(Threads REQUIRED)

find_package(GTest REQUIRED)

find_package(HDF5 COMPONENTS C CXX HL REQUIRED)

find_package(gmp REQUIRED)

find_package(sprng REQUIRED)

find_package(fftw REQUIRED)

include(Set_Lapack_Blas)

include(Set_Openmp_int64)

include(Set_Ext_Libraries)

add_subdirectory(common)
add_subdirectory(lanczos)
add_subdirectory(afqmc)
add_subdirectory(scripts)

file(RELATIVE_PATH relativeDirectorPath ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_LIST_DIR})
install(FILES afqmclab.h DESTINATION "include/${relativeDirectorPath}")

configure_file(AFQMCLABConfig.cmake.in "${PROJECT_BINARY_DIR}/AFQMCLABConfig.cmake" @ONLY)
install(FILES "${PROJECT_BINARY_DIR}/AFQMCLABConfig.cmake" DESTINATION cmake)

configure_file(AFQMCLABConfigVersion.cmake.in "${PROJECT_BINARY_DIR}/AFQMCLABConfigVersion.cmake" @ONLY)
install(FILES "${PROJECT_BINARY_DIR}/AFQMCLABConfigVersion.cmake" DESTINATION cmake)

install(DIRECTORY cmake DESTINATION cmake)