set(SOURCE_TESTS
        hop2SSD2SOperationTest.cpp)

add_executable(afqmcHop2SSD2SOperationTest ${SOURCE_HEADERS} ${SOURCE_TESTS} )

target_link_libraries(afqmcHop2SSD2SOperationTest afqmcHop2SSD2SOperationHao
        afqmcHop2SHao afqmcSD2SHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(afqmcHop2SSD2SOperationTest "$<TARGET_FILE:afqmcHop2SSD2SOperationTest>")
