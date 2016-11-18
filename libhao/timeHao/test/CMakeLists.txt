set(SOURCE_TESTS time_hao_test.cpp)

add_executable(timeTest ${SOURCE_HEADERS} ${SOURCE_TESTS})
target_link_libraries(timeTest timeHao testHao libgtest-main-hao
        ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${magma_libraries})
target_include_directories(timeTest PUBLIC ${GTEST_INCLUDE_DIRS})
add_my_test(timeTest "$<TARGET_FILE:timeTest>")