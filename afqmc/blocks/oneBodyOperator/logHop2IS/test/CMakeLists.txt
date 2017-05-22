set(SOURCE_TESTS
        logHop2ISTest.cpp)

add_executable(afqmcLogHop2ISTest ${SOURCE_HEADERS} ${SOURCE_TESTS})

target_link_libraries(afqmcLogHop2ISTest afqmcLogHop2ISHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(afqmcLogHop2ISTest "$<TARGET_FILE:afqmcLogHop2ISTest>")
