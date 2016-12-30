set(SOURCE_TESTS
        densityDensityOperatorTest.cpp)

add_executable(afqmcBlocksTwoBodyOperatorTest ${SOURCE_HEADERS} ${SOURCE_TESTS} )

target_link_libraries(afqmcBlocksTwoBodyOperatorTest afqmcBlocksTwoBodyOperatorHao
        commonHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(afqmcBlocksTwoBodyOperatorTest "$<TARGET_FILE:afqmcBlocksTwoBodyOperatorTest>")