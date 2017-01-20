set(SOURCE_TESTS
        afqmcMetropolisTest.cpp
        afqmcMetropolisMethodTest.cpp)

add_executable(afqmcMetropolisTest ${SOURCE_HEADERS} ${SOURCE_TESTS})

target_link_libraries(afqmcMetropolisTest afqmcMetropolisHao afqmcModelHao
        afqmcBlocksHao afqmcUtilitiesHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(afqmcMetropolisTest "$<TARGET_FILE:afqmcMetropolisTest>")