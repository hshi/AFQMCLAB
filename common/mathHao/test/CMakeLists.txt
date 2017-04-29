set(SOURCE_TESTS brents_fun_test.cpp simple_fun_test.cpp sort_fun_test.cpp polynomialFitTest.cpp)

add_executable(mathTest ${SOURCE_HEADERS}  ${SOURCE_TESTS})

target_link_libraries(mathTest mathHao tensorHao mpiHao testHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(mathTest "$<TARGET_FILE:mathTest>")