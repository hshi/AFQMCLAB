set(SOURCE_TESTS
        choleskyRealTest.cpp)

add_executable(afqmcCholeskyRealTest ${SOURCE_HEADERS} ${SOURCE_TESTS} )

target_link_libraries(afqmcCholeskyRealTest afqmcCholeskyRealHao afqmcLogHop2isHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(afqmcCholeskyRealTest "$<TARGET_FILE:afqmcCholeskyRealTest>")