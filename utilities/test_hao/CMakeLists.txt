add_library(libgtest-main-hao STATIC main.cpp gtest_custom.cpp gtest_custom.h)
target_include_directories(libgtest-main-hao PUBLIC ${GTEST_INCLUDE_DIRS})