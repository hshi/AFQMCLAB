#For source
set(SOURCE_HEADERS
        include/pfaffian_utilities.h
        include/tensor_2d_bl_magma.h
        include/tensor_all.h
        include/tensor_element_wise.h
        include/tensor_hao.h
        include/tensor_mpi.h
        include/tensor_1d_bl_cpu.h
        include/tensor_2d_bl_cpu.h
        include/tensor_2d_common_fun.h
        include/tensor_core.h
        include/tensor_fill.h
        include/tensor_hao_ref.h)

set(SOURCE_FILES
        source/tensor_1d_bl_cpu.cpp
        source/tensor_2d_bl_cpu.cpp
        source/tensor_2d_bl_magma.cpp
        source/tensor_2d_common_fun.cpp
        source/tensor_fill.cpp)

set(SOURCE_TESTS
        test/tensor_1d_bl_cpu_test.cpp
        test/tensor_2d_bl_cpu_test.cpp
        test/tensor_2d_common_fun_test.cpp
        test/tensor_element_wise_test.cpp
        test/tensor_hao_test.cpp
        test/tensor_2d_bl_magma_test.cpp
        test/tensor_core_test.cpp
        test/tensor_hao_ref_test.cpp
        test/tensor_mpi_test.cpp)

set(SOURCE_TIMING
        timing/bl_cpu_magma_timing.cpp
        timing/timing_all.cpp)

#For lapack and blas
add_definitions(${lapackblas_definitions})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${lapackblas_flags}")
removeDuplicateSubstring(${CMAKE_CXX_FLAGS} CMAKE_CXX_FLAGS)
include_directories(${lapackblas_include_dirs})

#For library
add_library(tensorHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(tensorHao STATIC $<TARGET_OBJECTS:tensorHaoObject>)

#For Test
add_executable(tensorTest ${SOURCE_HEADERS} ${SOURCE_TESTS})

set(ext_libraries ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${lapackblas_libraries})
list(REMOVE_DUPLICATES ext_libraries)
target_link_libraries(tensorTest tensorHao mpiHao testHao libgtest-main-hao ${ext_libraries})

target_include_directories(tensorTest PUBLIC ${GTEST_INCLUDE_DIRS})

add_my_test(tensorTest "$<TARGET_FILE:tensorTest>")

#For Timing
add_executable(tensorTiming ${SOURCE_HEADERS} ${SOURCE_TIMING})
target_link_libraries(tensorTiming tensorHao mpiHao ${lapackblas_libraries})

#For bin:diag_cpu
add_executable(diag_cpu ${SOURCE_HEADERS} bin/diag_cpu.cpp)
target_link_libraries(diag_cpu tensorHao mpiHao ${lapackblas_libraries})

#For bin:diag_magma
add_executable(diag_magma ${SOURCE_HEADERS} bin/diag_magma.cpp)
target_link_libraries(diag_magma tensorHao mpiHao ${lapackblas_libraries})