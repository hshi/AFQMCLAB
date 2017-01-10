set(SOURCE_TESTS
        SDTest.cpp)

add_executable(afqmcSDTest ${SOURCE_HEADERS} ${SOURCE_TESTS} )

target_link_libraries(afqmcSDTest afqmcSDHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(afqmcSDTest "$<TARGET_FILE:afqmcSDTest>")