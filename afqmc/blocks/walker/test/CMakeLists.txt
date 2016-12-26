set(SOURCE_TESTS
        singleDeterminantTest.cpp)

add_executable(afqmcBlocksWalkerTest ${SOURCE_HEADERS} ${SOURCE_TESTS} )

target_link_libraries(afqmcBlocksWalkerTest afqmcBlocksWalkerHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(afqmcBlocksWalkerTest "$<TARGET_FILE:afqmcBlocksWalkerTest>")