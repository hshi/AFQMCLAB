set(SOURCE_TESTS time_hao_test.cpp)

add_executable(timeTest ${SOURCE_HEADERS} ${SOURCE_TESTS})

target_link_libraries(timeTest timeHao testHao gtest_mainHao ${EXT_LIBRARIES} )

add_my_test(timeTest "$<TARGET_FILE:timeTest>")