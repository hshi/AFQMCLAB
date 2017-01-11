set(SOURCE_TESTS
        NiupNidnSDOperationTest.cpp)

add_executable(afqmcNiupNidnSDOperationTest ${SOURCE_HEADERS} ${SOURCE_TESTS} )

target_link_libraries(afqmcNiupNidnSDOperationTest afqmcNiupNidnSDOperationHao
        afqmcNiupNidnHao afqmcSDSDOperationHao afqmcSDHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(afqmcNiupNidnSDOperationTest "$<TARGET_FILE:afqmcNiupNidnSDOperationTest>")