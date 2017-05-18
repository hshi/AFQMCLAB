set(SOURCE_TESTS
        SD2ISTest.cpp)

add_executable(afqmcSD2ISTest ${SOURCE_HEADERS} ${SOURCE_TESTS} )

target_link_libraries(afqmcSD2ISTest afqmcSD2ISHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(afqmcSD2ISTest "$<TARGET_FILE:afqmcSD2ISTest>")