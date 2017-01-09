set(SOURCE_TESTS
        NiNjTest.cpp)

add_executable(afqmcNiNjTest ${SOURCE_HEADERS} ${SOURCE_TESTS} )

target_link_libraries(afqmcNiNjTest afqmcNiNjHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(afqmcNiNjTest "$<TARGET_FILE:afqmcNiNjTest>")