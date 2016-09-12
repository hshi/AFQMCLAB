#For source
set(SOURCE_HEADERS
        include/brents_fun.h
        include/math_container.h
        include/simple_fun.h
        include/sort_fun.h)

set(SOURCE_FILES
        source/brents_fun.cpp
        source/simple_fun.cpp)

set(SOURCE_TESTS
        test/brents_fun_test.cpp
        test/simple_fun_test.cpp
        test/sort_fun_test.cpp)

#For library
add_library(mathhao OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})

#For Test
add_executable(mathhaotest ${SOURCE_HEADERS} $<TARGET_OBJECTS:mathhao>
        ${SOURCE_TESTS} $<TARGET_OBJECTS:mpihao>)

target_link_libraries(mathhaotest libgtest-main-hao ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

target_include_directories(mathhaotest PUBLIC ${GTEST_INCLUDE_DIRS})

add_my_test(mathhaotest mathhaotest)