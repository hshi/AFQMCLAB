cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(AFQMCLIB  C CXX)

#For find module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

#Set platform
set(PLATFORM "DEFUALT" CACHE STRING "The platform to be run.")
include("PLATFORM_${PLATFORM}")

#Set flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#Enable test
enable_testing()

#Add custom functions
include(FUNCTION_CUSTOM)

#Set librarys
find_package(Threads REQUIRED)

find_package(GTest REQUIRED)

find_package(gmp REQUIRED)

find_package(sprng REQUIRED)

include(LAPACK_BLAS_ALL)

add_subdirectory(utilities)
add_subdirectory(lib_hao)