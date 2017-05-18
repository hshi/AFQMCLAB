set(SOURCE_TESTS
        hop2ISSD2ISOperationTest.cpp)

add_executable(afqmcHop2ISSD2ISOperationTest ${SOURCE_HEADERS} ${SOURCE_TESTS} )

target_link_libraries(afqmcHop2ISSD2ISOperationTest afqmcHop2ISSD2ISOperationHao
        afqmcHop2ISHao afqmcSD2ISHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(afqmcHop2ISSD2ISOperationTest "$<TARGET_FILE:afqmcHop2ISSD2ISOperationTest>")
