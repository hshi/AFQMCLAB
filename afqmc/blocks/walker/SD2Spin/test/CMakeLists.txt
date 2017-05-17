set(SOURCE_TESTS
        SD2SpinTest.cpp)

add_executable(afqmcSD2SpinTest ${SOURCE_HEADERS} ${SOURCE_TESTS} )

target_link_libraries(afqmcSD2SpinTest afqmcSD2SpinHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(afqmcSD2SpinTest "$<TARGET_FILE:afqmcSD2SpinTest>")