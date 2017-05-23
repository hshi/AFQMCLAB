set(SOURCE_TESTS
        SD2sSD2isOperationTest.cpp)

add_executable(afqmcSD2sSD2isOperationTest ${SOURCE_HEADERS} ${SOURCE_TESTS} )

target_link_libraries(afqmcSD2sSD2isOperationTest afqmcSD2sSD2isOperationHao afqmcSD2sHao afqmcSD2isHao
        commonHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(afqmcSD2sSD2isOperationTest "$<TARGET_FILE:afqmcSD2sSD2isOperationTest>")