set(SOURCE_TESTS
        doublePopType.h
        doublePopType.cpp
        populationControlTest.cpp)

add_executable(afqmcPopulationControlTest ${SOURCE_HEADERS} ${SOURCE_TESTS})

target_link_libraries(afqmcPopulationControlTest afqmcPopulationControlHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(afqmcPopulationControlTest "$<TARGET_FILE:afqmcPopulationControlTest>")