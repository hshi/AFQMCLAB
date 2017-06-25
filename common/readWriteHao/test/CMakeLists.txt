set(SOURCE_TESTS readWriteStringFileTest.cpp readWriteHdf5Test.cpp readBySearchStringTest.cpp)

add_executable(readWriteHaoTest ${SOURCE_HEADERS} ${SOURCE_TESTS})

target_link_libraries(readWriteHaoTest readWriteHao hdf5CustomHao mpiHao testHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(readWriteHaoTest "$<TARGET_FILE:readWriteHaoTest>")