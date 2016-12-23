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

target_link_libraries(tensorTest tensorHao mpiHao testHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(tensorTest "$<TARGET_FILE:tensorTest>")