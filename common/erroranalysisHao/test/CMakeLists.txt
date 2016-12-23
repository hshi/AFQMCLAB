set(SOURCE_TESTS kahan_test.cpp serialErrorAnalysisTest.cpp threadErrorAnalysisTest.cpp)

add_executable(errorAnalysisTest ${SOURCE_HEADERS} ${SOURCE_TESTS})

target_link_libraries(errorAnalysisTest errorAnalysisHao mpiHao testHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(errorAnalysisTest "$<TARGET_FILE:errorAnalysisTest>")