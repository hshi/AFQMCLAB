set(SOURCE_TESTS
        tensor_1d_bl_cpu_test.cpp
        tensor_2d_bl_cpu_test.cpp
        tensor_2d_common_fun_test.cpp
        tensor_element_wise_test.cpp
        tensor_hao_test.cpp
        tensor_2d_bl_magma_test.cpp
        tensor_core_test.cpp
        tensor_hao_ref_test.cpp
        tensor_mpi_test.cpp)

add_executable(tensorTest ${SOURCE_HEADERS} ${SOURCE_TESTS})

set(ext_libraries ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${lapackblas_libraries})
list(REMOVE_DUPLICATES ext_libraries)

target_link_libraries(tensorTest tensorHao mpiHao testHao libgtest-main-hao ${ext_libraries})

target_include_directories(tensorTest PUBLIC ${GTEST_INCLUDE_DIRS})

add_my_test(tensorTest "$<TARGET_FILE:tensorTest>")