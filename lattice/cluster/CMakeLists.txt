#For source
set(SOURCE_HEADERS cluster.h)
set(SOURCE_FILES cluster.cpp)
set(SOURCE_TESTS clusterTest.cpp)

#For library
add_library(clusterHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(clusterHao STATIC $<TARGET_OBJECTS:clusterHaoObject>)

#For Test
add_executable(clusterTest ${SOURCE_HEADERS} ${SOURCE_TESTS})

target_link_libraries(clusterTest clusterHao libHao libgtest-main-hao ${ext_libraries})

target_include_directories(clusterTest PUBLIC ${ext_include_dirs})

add_my_test(clusterTest "$<TARGET_FILE:clusterTest>")