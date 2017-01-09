set(SOURCE_TESTS
        singleDeterminantTest.cpp)

add_executable(afqmcSingleDeterminantTest ${SOURCE_HEADERS} ${SOURCE_TESTS} )

target_link_libraries(afqmcSingleDeterminantTest afqmcSingleDeterminantHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(afqmcSingleDeterminantTest "$<TARGET_FILE:afqmcSingleDeterminantTest>")