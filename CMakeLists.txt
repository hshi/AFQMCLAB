cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(AFQMCLIB  C CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

set(PLATFORM "DEFUALT" CACHE STRING "The platform to be run.")
include("PLATFORM_${PLATFORM}")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

include(FUNCTION_CUSTOM)

setInt64IfDefineUSE_INT64()

removeDuplicateSubstring(${CMAKE_CXX_FLAGS} CMAKE_CXX_FLAGS)

#Set librarys
find_package(Threads REQUIRED)

find_package(GTest REQUIRED)

find_package(gmp REQUIRED)

find_package(sprng REQUIRED)

find_package(fftw REQUIRED)

include(Set_Lapack_Blas)

include(Set_Openmp)

include(Set_Ext_Libraries)

add_subdirectory(libhao)
add_subdirectory(lattice)
add_subdirectory(model)
add_subdirectory(Lanczos)
