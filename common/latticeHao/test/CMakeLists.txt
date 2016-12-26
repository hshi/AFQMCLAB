set(SOURCE_TESTS clusterTest.cpp supercubicTest.cpp)

add_executable(latticeHaoTest ${SOURCE_HEADERS} ${SOURCE_TESTS} )

target_link_libraries(latticeHaoTest latticeHao readWriteHao mpiHao testHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(latticeHaoTest "$<TARGET_FILE:latticeHaoTest>")