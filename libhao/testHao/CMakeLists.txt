#For testHao libraries
include_directories(${GTEST_INCLUDE_DIRS})
add_library(testHaoObject OBJECT gtest_custom.h gtest_custom.cpp)
add_library(testHao STATIC $<TARGET_OBJECTS:testHaoObject>)

#For testHao main function
add_definitions(${magma_definitions})
include_directories(${magma_include_dirs})
add_library(libgtest-main-hao STATIC main.cpp)

#Install
file(RELATIVE_PATH relativeDirectorPath ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_LIST_DIR})
install(FILES gtest_custom.h DESTINATION "include/${relativeDirectorPath}")