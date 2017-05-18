set(SOURCE_TESTS
        hop2STest.cpp)

add_executable(afqmcHop2STest ${SOURCE_HEADERS} ${SOURCE_TESTS})

target_link_libraries(afqmcHop2STest afqmcHop2SHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(afqmcHop2STest "$<TARGET_FILE:afqmcHop2STest>")
