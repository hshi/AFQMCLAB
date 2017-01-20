cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(lanczosHubbard C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

find_package(AFQMCLAB REQUIRED)

set(CMAKE_CXX_COMPILER ${AFQMCLAB_COMPILER})
include_directories(${AFQMCLAB_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${AFQMCLAB_FLAGS}")
add_definitions(${AFQMCLAB_DEFINITIONS})

set(SOURCE_HEADERS
        ${CMAKE_CURRENT_LIST_DIR}/include/afqmcMetropolis.h
        ${CMAKE_CURRENT_LIST_DIR}/include/afqmcMetropolisMethod.h
        )

add_subdirectory(source)