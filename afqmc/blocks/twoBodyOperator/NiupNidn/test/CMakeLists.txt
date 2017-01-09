set(SOURCE_TESTS
        NiupNidnTest.cpp
        NiupNidnSampleTest.cpp)

add_executable(afqmcNiupNidnTest ${SOURCE_HEADERS} ${SOURCE_TESTS} )

target_link_libraries(afqmcNiupNidnTest afqmcNiupNidnHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(afqmcNiupNidnTest "$<TARGET_FILE:afqmcNiupNidnTest>")