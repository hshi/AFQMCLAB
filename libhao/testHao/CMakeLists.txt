#For testHao libraries
add_library(testHaoObject OBJECT gtest_custom.h gtest_custom.cpp)
add_library(testHao STATIC $<TARGET_OBJECTS:testHaoObject>)

#For testHao main function
add_library(libgtest-main-hao STATIC main.cpp)

#Install
file(RELATIVE_PATH relativeDirectorPath ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_LIST_DIR})
install(FILES gtest_custom.h DESTINATION "include/${relativeDirectorPath}")