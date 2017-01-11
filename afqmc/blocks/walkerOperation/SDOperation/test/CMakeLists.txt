set(SOURCE_TESTS
        SDOperationTest.cpp)

add_executable(afqmcSDOperationTest ${SOURCE_HEADERS} ${SOURCE_TESTS} )

target_link_libraries(afqmcSDOperationTest afqmcSDOperationHao afqmcSDHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(afqmcSDOperationTest "$<TARGET_FILE:afqmcSDOperationTest>")