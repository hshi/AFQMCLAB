set(SOURCE_TESTS
        writeThreadSumTest.cpp)

add_executable(afqmcManipulateMCDataTest ${SOURCE_HEADERS} ${SOURCE_TESTS})

target_link_libraries(afqmcManipulateMCDataTest afqmcManipulateMCDataHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(afqmcManipulateMCDataTest "$<TARGET_FILE:afqmcManipulateMCDataTest>")