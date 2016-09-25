include_directories(${GTEST_INCLUDE_DIRS})

add_library(testHaoObject OBJECT gtest_custom.h gtest_custom.cpp)
add_library(testHao STATIC $<TARGET_OBJECTS:testHaoObject>)

add_library(libgtest-main-hao STATIC main.cpp)