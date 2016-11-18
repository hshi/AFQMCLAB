set(SOURCE_TESTS random_hao_test.cpp)

add_executable(randomNumberTest ${SOURCE_HEADERS} ${SOURCE_TESTS})

set(ext_libraries ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${magma_libraries} ${sprng_libraries} ${gmp_libraries})
list(REMOVE_DUPLICATES ext_libraries)
target_link_libraries(randomNumberTest randomNumberHao mpiHao testHao libgtest-main-hao ${ext_libraries})

target_include_directories(randomNumberTest PUBLIC ${GTEST_INCLUDE_DIRS})

add_my_test(randomNumberTest "$<TARGET_FILE:randomNumberTest>")