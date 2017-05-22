set(SOURCE_TESTS
        logHop2isTest.cpp)

add_executable(afqmcLogHop2isTest ${SOURCE_HEADERS} ${SOURCE_TESTS})

target_link_libraries(afqmcLogHop2isTest afqmcLogHop2isHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(afqmcLogHop2isTest "$<TARGET_FILE:afqmcLogHop2isTest>")
