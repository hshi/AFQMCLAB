set(SOURCE_TESTS
        SD2isTest.cpp)

add_executable(afqmcSD2isTest ${SOURCE_HEADERS} ${SOURCE_TESTS} )

target_link_libraries(afqmcSD2isTest afqmcSD2isHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(afqmcSD2isTest "$<TARGET_FILE:afqmcSD2isTest>")
