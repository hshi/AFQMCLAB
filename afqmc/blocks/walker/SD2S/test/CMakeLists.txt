set(SOURCE_TESTS
        SD2STest.cpp)

add_executable(afqmcSD2STest ${SOURCE_HEADERS} ${SOURCE_TESTS} )

target_link_libraries(afqmcSD2STest afqmcSD2SHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(afqmcSD2STest "$<TARGET_FILE:afqmcSD2STest>")
