set(SOURCE_TESTS kahan_test.cpp serialErrorAnalysisTest.cpp thread_error_analysis_test.cpp)

add_executable(errorAnalysisTest ${SOURCE_HEADERS} ${SOURCE_TESTS})

target_link_libraries(errorAnalysisTest errorAnalysisHao mpiHao testHao libgtest-main-hao
        ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${magma_libraries})

target_include_directories(errorAnalysisTest PUBLIC ${GTEST_INCLUDE_DIRS})

add_my_test(errorAnalysisTest "$<TARGET_FILE:errorAnalysisTest>")