set(SOURCE_TESTS
        SDSDOperationTest.cpp)

add_executable(afqmcSDSDOperationTest ${SOURCE_HEADERS} ${SOURCE_TESTS} )

target_link_libraries(afqmcSDSDOperationTest afqmcSDSDOperationHao afqmcSDHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(afqmcSDSDOperationTest "$<TARGET_FILE:afqmcSDSDOperationTest>")