cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(afqmcMetropolis C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

find_package(AFQMCLAB REQUIRED)

set(CMAKE_CXX_COMPILER ${AFQMCLAB_COMPILER})
include_directories(${AFQMCLAB_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${AFQMCLAB_FLAGS}")
add_definitions(${AFQMCLAB_DEFINITIONS})

set(SOURCE_HEADERS
        include/afqmcMetropolis.h
        include/afqmcMetropolisMethod.h
        )

set(SOURCE_FILES
        source/afqmcMetropolis.cpp
        source/afqmcMetropolisMeasure.cpp
        source/afqmcMetropolisSetWalkerAndField.cpp
        source/afqmcMetropolisMethod.cpp
        source/afqmcMetropolisUpdate.cpp
        source/main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_HEADERS} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${AFQMCLAB_LIBRARIES})

add_custom_target(rmdat COMMAND rm -rf *dat)