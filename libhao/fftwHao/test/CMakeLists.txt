set(SOURCE_TESTS fftw_hao_test.cpp)

add_executable(fftwTest ${SOURCE_HEADERS} ${SOURCE_TESTS})

set(ext_libraries ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${magma_libraries} ${fftw_libraries})
list(REMOVE_DUPLICATES ext_libraries)
target_link_libraries(fftwTest fftwHao mpiHao testHao libgtest-main-hao ${ext_libraries})

target_include_directories(fftwTest PUBLIC ${GTEST_INCLUDE_DIRS})

add_my_test(fftwTest "$<TARGET_FILE:fftwTest>")