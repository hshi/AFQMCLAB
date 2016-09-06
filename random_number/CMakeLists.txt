#For source
set(SOURCE_HEADERS include/random_hao.h)

set(SOURCE_FILES source/random_hao.cpp)

set(SOURCE_TESTS test/random_hao_test.cpp)

#For sprng
add_definitions(${sprng_definitions})

#For library
add_library(randomnumber OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
target_include_directories(randomnumber PUBLIC ${sprng_include_dirs})

#For Test
add_executable(randomnumbertest ${SOURCE_HEADERS} $<TARGET_OBJECTS:randomnumber>
        ${SOURCE_TESTS} $<TARGET_OBJECTS:mpihao>)

target_link_libraries(randomnumbertest libgtest-main-hao ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT}
        ${sprng_libraries} ${gmp_libraries})

target_include_directories(randomnumbertest PUBLIC ${GTEST_INCLUDE_DIRS} ${sprng_include_dirs})

add_my_test(randomnumbertest randomnumbertest)