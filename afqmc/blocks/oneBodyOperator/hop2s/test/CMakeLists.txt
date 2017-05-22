set(SOURCE_TESTS
        hop2sTest.cpp)

add_executable(afqmcHop2sTest ${SOURCE_HEADERS} ${SOURCE_TESTS})

target_link_libraries(afqmcHop2sTest afqmcHop2sHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(afqmcHop2sTest "$<TARGET_FILE:afqmcHop2sTest>")
