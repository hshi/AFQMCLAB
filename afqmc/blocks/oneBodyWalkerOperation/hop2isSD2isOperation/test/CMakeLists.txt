set(SOURCE_TESTS
        hop2isSD2isOperationTest.cpp)

add_executable(afqmcHop2isSD2isOperationTest ${SOURCE_HEADERS} ${SOURCE_TESTS} )

target_link_libraries(afqmcHop2isSD2isOperationTest afqmcHop2isSD2isOperationHao
        afqmcHop2isHao afqmcSD2isHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(afqmcHop2isSD2isOperationTest "$<TARGET_FILE:afqmcHop2isSD2isOperationTest>")
