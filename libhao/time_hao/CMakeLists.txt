#For source
set(SOURCE_HEADERS time_hao.h)
set(SOURCE_FILES time_hao.cpp)
set(SOURCE_TESTS time_hao_test.cpp)

#For library
add_library(timeHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(timeHao STATIC $<TARGET_OBJECTS:timeHaoObject>)

#For Test
add_executable(timeTest ${SOURCE_HEADERS} ${SOURCE_TESTS})
target_link_libraries(timeTest timeHao testHao libgtest-main-hao ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(timeTest PUBLIC ${GTEST_INCLUDE_DIRS})
add_my_test(timeTest "$<TARGET_FILE:timeTest>")