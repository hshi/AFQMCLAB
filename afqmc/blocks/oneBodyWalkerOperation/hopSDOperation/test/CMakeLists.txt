set(SOURCE_TESTS
        hopSDOperationTest.cpp)

add_executable(afqmcHopSDOperationTest ${SOURCE_HEADERS} ${SOURCE_TESTS} )

target_link_libraries(afqmcHopSDOperationTest afqmcHopSDOperationHao
        afqmcHopHao afqmcSDHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(afqmcHopSDOperationTest "$<TARGET_FILE:afqmcHopSDOperationTest>")