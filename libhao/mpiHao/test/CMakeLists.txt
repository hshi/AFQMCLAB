set(SOURCE_TESTS mpi_fun_test.cpp)

add_executable(mpiTest ${SOURCE_HEADERS} ${SOURCE_TESTS})
target_link_libraries(mpiTest mpiHao testHao libgtest-main-hao
        ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${magma_libraries})
target_include_directories(mpiTest PUBLIC ${GTEST_INCLUDE_DIRS})
add_my_test(mpiTest "$<TARGET_FILE:mpiTest>")