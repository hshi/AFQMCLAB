set(SOURCE_TESTS
        hop2SpinTest.cpp)

add_executable(afqmcHop2SpinTest ${SOURCE_HEADERS} ${SOURCE_TESTS})

target_link_libraries(afqmcHop2SpinTest afqmcHop2SpinHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(afqmcHop2SpinTest "$<TARGET_FILE:afqmcHop2SpinTest>")