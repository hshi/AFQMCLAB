set(SOURCE_TESTS
        createZeroUInputFile.cpp
        HubbardSOCTest.cpp
        HubbardSOCMeasureSDSDTest.cpp
        HubbardSOCMeasureFixedSDSDTest.cpp)

add_executable(afqmcHubbardRealSpaceSOCTest ${SOURCE_HEADERS} ${SOURCE_TESTS})

target_link_libraries(afqmcHubbardRealSpaceSOCTest afqmcHubbardRealSpaceSOCHao afqmcUtilitiesHao afqmcBlocksHao
        commonHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(afqmcHubbardRealSpaceSOCTest "$<TARGET_FILE:afqmcHubbardRealSpaceSOCTest>")