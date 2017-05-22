set(SOURCE_TESTS
        hop2sSD2sOperationTest.cpp)

add_executable(afqmcHop2sSD2sOperationTest ${SOURCE_HEADERS} ${SOURCE_TESTS} )

target_link_libraries(afqmcHop2sSD2sOperationTest afqmcHop2sSD2sOperationHao
        afqmcHop2sHao afqmcSD2sHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(afqmcHop2sSD2sOperationTest "$<TARGET_FILE:afqmcHop2sSD2sOperationTest>")
