set(SOURCE_TESTS lanczosBasisTest.cpp)

add_executable(lanczosBasisTest ${SOURCE_HEADERS} ${SOURCE_TESTS})

target_link_libraries(lanczosBasisTest lanczosBasisHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_test( NAME lanczosBasisTest COMMAND "$<TARGET_FILE:lanczosBasisTest>")