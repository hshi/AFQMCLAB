set(SOURCE_TESTS
        hopTest.cpp)

add_executable(afqmcHopTest ${SOURCE_HEADERS} ${SOURCE_TESTS})

target_link_libraries(afqmcHopTest afqmcHopHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(afqmcHopTest "$<TARGET_FILE:afqmcHopTest>")