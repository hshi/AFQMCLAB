cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(AFQMCLIB C CXX)

set(AFQMC_MAJOR_VERSION 0)
set(AFQMC_MINOR_VERSION 1)
set(AFQMC_PATCH_VERSION 0)
set(AFQMC_VERSION ${AFQMC_MAJOR_VERSION}.${AFQMC_MINOR_VERSION}.${AFQMC_PATCH_VERSION})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

set(PLATFORM "DEFUALT" CACHE STRING "The platform to be run.")
include("PLATFORM_${PLATFORM}")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

include(FUNCTION_CUSTOM)

#Set librarys
find_package(Threads REQUIRED)

find_package(GTest REQUIRED)

find_package(gmp REQUIRED)

find_package(sprng REQUIRED)

find_package(fftw REQUIRED)

include(Set_Lapack_Blas)

include(Set_Openmp_int64)

include(Set_Ext_Libraries)

add_subdirectory(common)
add_subdirectory(lanczos)
add_subdirectory(model)
add_subdirectory(scripts)

file(RELATIVE_PATH relativeDirectorPath ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_LIST_DIR})
install(FILES afqmc.h DESTINATION "include/${relativeDirectorPath}")

configure_file(AFQMCConfig.cmake.in "${PROJECT_BINARY_DIR}/AFQMCConfig.cmake" @ONLY)
install(FILES "${PROJECT_BINARY_DIR}/AFQMCConfig.cmake" DESTINATION cmake)

configure_file(AFQMCConfigVersion.cmake.in "${PROJECT_BINARY_DIR}/AFQMCConfigVersion.cmake" @ONLY)
install(FILES "${PROJECT_BINARY_DIR}/AFQMCConfigVersion.cmake" DESTINATION cmake)

install(DIRECTORY cmake DESTINATION cmake)