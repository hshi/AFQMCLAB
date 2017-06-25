set(SOURCE_TESTS
        afqmcPhaselessMethodTest.cpp)

add_executable(afqmcPhaselessTest ${SOURCE_HEADERS} ${SOURCE_TESTS})

target_link_libraries(afqmcPhaselessTest afqmcPhaselessHao afqmcModelHao
        afqmcBlocksHao afqmcUtilitiesHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(afqmcPhaselessTest "$<TARGET_FILE:afqmcPhaselessTest>")