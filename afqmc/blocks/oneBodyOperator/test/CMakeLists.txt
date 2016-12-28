set(SOURCE_TESTS
        hoppingOperatorTest.cpp)

add_executable(afqmcBlocksOneBodyOperatorTest ${SOURCE_HEADERS} ${SOURCE_TESTS} )

target_link_libraries(afqmcBlocksOneBodyOperatorTest afqmcBlocksOneBodyOperatorHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(afqmcBlocksOneBodyOperatorTest "$<TARGET_FILE:afqmcBlocksOneBodyOperatorTest>")