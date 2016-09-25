#For source
set(SOURCE_HEADERS cluster.h)
set(SOURCE_FILES cluster.cpp)
set(SOURCE_TESTS cluster_test.cpp)

#For library
add_library(clusterHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(clusterHao STATIC $<TARGET_OBJECTS:clusterHaoObject>)

#For Test
add_executable(clusterTest ${SOURCE_HEADERS} ${SOURCE_TESTS})

target_link_libraries(clusterTest clusterHao mpiHao testHao
        libgtest-main-hao ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

target_include_directories(clusterTest PUBLIC ${GTEST_INCLUDE_DIRS})

add_my_test(clusterTest clusterTest)