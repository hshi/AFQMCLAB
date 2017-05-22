set(SOURCE_TESTS
        SD2sTest.cpp)

add_executable(afqmcSD2sTest ${SOURCE_HEADERS} ${SOURCE_TESTS} )

target_link_libraries(afqmcSD2sTest afqmcSD2sHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(afqmcSD2sTest "$<TARGET_FILE:afqmcSD2sTest>")
