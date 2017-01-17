set(SOURCE_TESTS
        afqmcMetropolisTest.cpp
        afqmcMetropolisMethodTest.cpp)

add_executable(afqmcMetropolisHubbardSDSDTest ${SOURCE_HEADERS} ${SOURCE_TESTS})

target_link_libraries(afqmcMetropolisHubbardSDSDTest afqmcMetropolisHubbardSDSDHao afqmcModelHao
        afqmcBlocksHao afqmcUtilitiesHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(afqmcMetropolisHubbardSDSDTest "$<TARGET_FILE:afqmcMetropolisHubbardSDSDTest>")