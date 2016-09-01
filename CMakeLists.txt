cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(AFQMCLIB)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(AFQMCLIB ${SOURCE_FILES})