cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(helloAfqmc C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

find_package(AFQMC REQUIRED)

set(CMAKE_CXX_COMPILER ${AFQMC_COMPILER})
include_directories(${AFQMC_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${AFQMC_FLAGS}")
add_definitions(${AFQMC_DEFINITIONS})

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${AFQMC_LIBRARIES})