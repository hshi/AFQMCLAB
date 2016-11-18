set(SOURCE_TESTS mpi_fun_test.cpp)

add_executable(mpiTest ${SOURCE_HEADERS} ${SOURCE_TESTS})

target_link_libraries(mpiTest mpiHao testHao libgtest-main-hao ${EXT_LIBRARIES})

add_my_test(mpiTest "$<TARGET_FILE:mpiTest>")