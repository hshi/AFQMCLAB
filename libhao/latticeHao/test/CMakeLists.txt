set(SOURCE_TESTS clusterTest.cpp supercubicTest.cpp)

add_executable(latticeHaoTest ${SOURCE_HEADERS} ${SOURCE_TESTS} )

target_link_libraries(latticeHaoTest latticeHao readWriteHao mpiHao testHao gtest_main_hao ${EXT_LIBRARIES})

add_test(NAME latticeHaoTest COMMAND "$<TARGET_FILE:latticeHaoTest>")