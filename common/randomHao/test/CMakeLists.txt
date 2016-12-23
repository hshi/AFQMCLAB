set(SOURCE_TESTS random_hao_test.cpp)

add_executable(randomNumberTest ${SOURCE_HEADERS} ${SOURCE_TESTS})

target_link_libraries(randomNumberTest randomNumberHao mpiHao testHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(randomNumberTest "$<TARGET_FILE:randomNumberTest>")