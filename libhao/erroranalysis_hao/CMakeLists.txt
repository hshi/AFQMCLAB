#We can temporarily set CMAKE_CXX_FLAGS, it will not affect other directory (Checked on my local computer)
#set(CMAKE_CXX_FLAGS "-std=c++11")

#For source
set(SOURCE_HEADERS
        include/kahan.h
        include/error_analysis.h
        include/thread_error_analysis.h)

set(SOURCE_FILES
        source/kahan.cpp
        source/error_analysis.cpp
        source/thread_error_analysis.cpp)

set(SOURCE_TESTS
        test/kahan_test.cpp
        test/error_analysis_test.cpp
        test/thread_error_analysis_test.cpp)

#For library
add_library(errorAnalysisHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(errorAnalysisHao STATIC $<TARGET_OBJECTS:errorAnalysisHaoObject>)

#For Test
add_executable(errorAnalysisTest ${SOURCE_HEADERS} ${SOURCE_TESTS})

target_link_libraries(errorAnalysisTest errorAnalysisHao mpiHao testHao
        libgtest-main-hao ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

target_include_directories(errorAnalysisTest PUBLIC ${GTEST_INCLUDE_DIRS})

add_my_test(errorAnalysisTest errorAnalysisTest)