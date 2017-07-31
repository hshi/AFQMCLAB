set(SOURCE_TESTS
        logHop2isSD2isOperationTest.cpp)

add_executable(afqmcLogHop2isSD2isOperationTest ${SOURCE_HEADERS} ${SOURCE_TESTS} )

target_link_libraries(afqmcLogHop2isSD2isOperationTest afqmcLogHop2isSD2isOperationHao
        afqmcLogHop2isHao afqmcSD2isHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(afqmcLogHop2isSD2isOperationTest "$<TARGET_FILE:afqmcLogHop2isSD2isOperationTest>")