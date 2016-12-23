set(SOURCE_TESTS readWriteHaoTest.cpp)

add_executable(readWriteHaoTest ${SOURCE_HEADERS} ${SOURCE_TESTS})

target_link_libraries(readWriteHaoTest readWriteHao mpiHao testHao gtest_main_hao ${EXT_LIBRARIES})

add_my_test(readWriteHaoTest "$<TARGET_FILE:readWriteHaoTest>")