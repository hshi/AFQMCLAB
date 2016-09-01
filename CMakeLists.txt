cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(AFQMCLIB)

#For find module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

#Set platform
set(PLATFORM "DEFUALT" CACHE STRING "The platform to be run.")
include("PLATFORM_${PLATFORM}")

#Set flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(AFQMCLIB ${SOURCE_FILES})