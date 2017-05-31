set(SOURCE_TESTS hdf5CustomHaoTest.cpp)

add_executable(hdf5CustomHaoTest ${SOURCE_HEADERS} ${SOURCE_TESTS})

target_link_libraries(hdf5CustomHaoTest hdf5CustomHao mpiHao testHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(hdf5CustomHaoTest "$<TARGET_FILE:hdf5CustomHaoTest>")