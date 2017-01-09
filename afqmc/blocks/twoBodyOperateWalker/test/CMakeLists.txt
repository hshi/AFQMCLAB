set(SOURCE_TESTS
        onSiteDensityUpDensityDnOperateSingleDeterminantTest.cpp)

add_executable(afqmcBlocksTwoBodyOperateWalerTest ${SOURCE_HEADERS} ${SOURCE_TESTS} )

target_link_libraries(afqmcBlocksTwoBodyOperateWalerTest afqmcBlocksTwoBodyOperateWalerHao
        afqmcBlocksTwoBodyOperatorHao afqmcBlocksWalkerHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(afqmcBlocksTwoBodyOperateWalerTest "$<TARGET_FILE:afqmcBlocksTwoBodyOperateWalerTest>")