set(SOURCE_TESTS
        afqmcConstraintPathMethodTest.cpp
        afqmcConstraintPathTest.cpp)

add_executable(afqmcConstraintPathTest ${SOURCE_HEADERS} ${SOURCE_TESTS})

target_link_libraries(afqmcConstraintPathTest afqmcConstraintPathHao afqmcModelHao
        afqmcBlocksHao afqmcUtilitiesHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(afqmcConstraintPathTest "$<TARGET_FILE:afqmcConstraintPathTest>")