#For source
set(SOURCE_HEADERS include/time_hao.h)

set(SOURCE_FILES source/time_hao.cpp)

set(SOURCE_TESTS test/time_hao_test.cpp)


#For library
add_library(timehao OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})


#For Test
add_executable(timetest ${SOURCE_HEADERS} $<TARGET_OBJECTS:timehao> ${SOURCE_TESTS})

target_link_libraries(timetest libgtest-main-hao ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

target_include_directories(timetest PUBLIC ${GTEST_INCLUDE_DIRS})

add_my_test(timetest timetest)