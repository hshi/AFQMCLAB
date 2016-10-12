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
add_library(mathHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(mathHao STATIC $<TARGET_OBJECTS:mathHaoObject>)

#For Test
add_executable(mathTest ${SOURCE_HEADERS}  ${SOURCE_TESTS})
target_link_libraries(mathTest mathHao mpiHao testHao
        libgtest-main-hao ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${magma_libraries})

target_include_directories(mathTest PUBLIC ${GTEST_INCLUDE_DIRS})

add_my_test(mathTest "$<TARGET_FILE:mathTest>")
