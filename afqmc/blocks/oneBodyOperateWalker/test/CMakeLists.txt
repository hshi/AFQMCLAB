set(SOURCE_TESTS
        hoppingOperateSingleDeterminantTest.cpp)

add_executable(afqmcBlocksOneBodyOperateWalerTest ${SOURCE_HEADERS} ${SOURCE_TESTS} )

target_link_libraries(afqmcBlocksOneBodyOperateWalerTest afqmcBlocksOneBodyOperateWalerHao
        afqmcBlocksOneBodyOperatorHao afqmcBlocksWalkerHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(afqmcBlocksOneBodyOperateWalerTest "$<TARGET_FILE:afqmcBlocksOneBodyOperateWalerTest>")