set(SOURCE_TESTS
        hopSingleDeterminantOperationTest.cpp)

add_executable(afqmcHopSingleDeterminantOperationTest ${SOURCE_HEADERS} ${SOURCE_TESTS} )

target_link_libraries(afqmcHopSingleDeterminantOperationTest afqmcHopSingleDeterminantOperationHao
        afqmcHopHao afqmcSingleDeterminantHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(afqmcHopSingleDeterminantOperationTest "$<TARGET_FILE:afqmcHopSingleDeterminantOperationTest>")