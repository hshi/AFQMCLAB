set(SOURCE_TESTS
        logHop2ISSD2ISOperationTest.cpp)

add_executable(afqmcLogHop2ISSD2ISOperationTest ${SOURCE_HEADERS} ${SOURCE_TESTS} )

target_link_libraries(afqmcLogHop2ISSD2ISOperationTest afqmcLogHop2ISSD2ISOperationHao
        afqmcLogHop2ISHao afqmcSD2ISHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(afqmcLogHop2ISSD2ISOperationTest "$<TARGET_FILE:afqmcLogHop2ISSD2ISOperationTest>")
