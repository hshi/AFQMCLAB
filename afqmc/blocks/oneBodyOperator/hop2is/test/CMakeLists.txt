set(SOURCE_TESTS
        hop2isTest.cpp)

add_executable(afqmcHop2isTest ${SOURCE_HEADERS} ${SOURCE_TESTS})

target_link_libraries(afqmcHop2isTest afqmcHop2isHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(afqmcHop2isTest "$<TARGET_FILE:afqmcHop2isTest>")
