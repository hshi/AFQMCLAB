set(SOURCE_TESTS fftw_hao_test.cpp)

add_executable(fftwTest ${SOURCE_HEADERS} ${SOURCE_TESTS})

target_link_libraries(fftwTest fftwHao mpiHao testHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(fftwTest "$<TARGET_FILE:fftwTest>")