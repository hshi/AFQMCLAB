#For source
set(SOURCE_HEADERS
        include/blas_lapack_customized.h
        include/pfaffian_utilities.h
        include/tensor_2d_bl_magma.h
        include/tensor_all.h
        include/tensor_element_wise.h
        include/tensor_hao.h
        include/tensor_mpi.h
        include/blas_lapack_wrap.h
        include/tensor_2d_bl_cpu.h
        include/tensor_2d_common_fun.h
        include/tensor_core.h
        include/tensor_fill.h
        include/tensor_hao_ref.h)

set(SOURCE_FILES
        source/tensor_2d_bl_cpu.cpp
        source/tensor_2d_bl_magma.cpp
        source/tensor_2d_common_fun.cpp
        source/tensor_fill.cpp)

set(SOURCE_TESTS
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

#For library
add_library(tensorhao OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
target_include_directories(tensorhao PUBLIC ${lapackblas_include_dirs} ${magma_cuda_include_dirs})

#For Test
add_executable(tensorhaotest ${SOURCE_HEADERS} $<TARGET_OBJECTS:tensorhao>
        ${SOURCE_TESTS} $<TARGET_OBJECTS:mpihao>)

target_link_libraries(tensorhaotest libgtest-main-hao ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT}
        ${lapackblas_libraries} ${magma_cuda_libraries})

target_include_directories(tensorhaotest PUBLIC ${GTEST_INCLUDE_DIRS} ${lapackblas_include_dirs} ${magma_cuda_include_dirs})

add_my_test(tensorhaotest tensorhaotest)

#For Timing
add_executable(tensorhaotiming ${SOURCE_HEADERS} $<TARGET_OBJECTS:tensorhao> ${SOURCE_TIMING} $<TARGET_OBJECTS:mpihao>)

target_link_libraries(tensorhaotiming ${lapackblas_libraries} ${magma_cuda_libraries})

target_include_directories(tensorhaotiming PUBLIC ${lapackblas_include_dirs} ${magma_cuda_include_dirs})

#For bin:diag_cpu
add_executable(diag_cpu ${SOURCE_HEADERS} $<TARGET_OBJECTS:tensorhao> bin/diag_cpu.cpp $<TARGET_OBJECTS:mpihao>)

target_link_libraries(diag_cpu ${lapackblas_libraries} ${magma_cuda_libraries})

target_include_directories(diag_cpu PUBLIC ${lapackblas_include_dirs} ${magma_cuda_include_dirs})

#For bin:diag_magma
add_executable(diag_magma ${SOURCE_HEADERS} $<TARGET_OBJECTS:tensorhao> bin/diag_magma.cpp $<TARGET_OBJECTS:mpihao>)

target_link_libraries(diag_magma ${lapackblas_libraries} ${magma_cuda_libraries})

target_include_directories(diag_magma PUBLIC ${lapackblas_include_dirs} ${magma_cuda_include_dirs})