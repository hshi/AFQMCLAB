set(SOURCE_TESTS brents_fun_test.cpp simple_fun_test.cpp sort_fun_test.cpp)

add_executable(mathTest ${SOURCE_HEADERS}  ${SOURCE_TESTS})
target_link_libraries(mathTest mathHao mpiHao testHao libgtest-main-hao
        ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${magma_libraries})

target_include_directories(mathTest PUBLIC ${GTEST_INCLUDE_DIRS})

add_my_test(mathTest "$<TARGET_FILE:mathTest>")