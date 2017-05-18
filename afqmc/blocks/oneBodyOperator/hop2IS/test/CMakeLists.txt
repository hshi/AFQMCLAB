set(SOURCE_TESTS
        hop2ISTest.cpp)

add_executable(afqmcHop2ISTest ${SOURCE_HEADERS} ${SOURCE_TESTS})

target_link_libraries(afqmcHop2ISTest afqmcHop2ISHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(afqmcHop2ISTest "$<TARGET_FILE:afqmcHop2ISTest>")
