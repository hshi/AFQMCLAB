#For source
set(SOURCE_HEADERS random_hao.h)

set(SOURCE_FILES random_hao.cpp)

set(SOURCE_TESTS random_hao_test.cpp)

#For sprng
add_definitions(${sprng_definitions})
include_directories(${sprng_include_dirs})

#For library
add_library(randomNumberHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(randomNumberHao STATIC $<TARGET_OBJECTS:randomNumberHaoObject>)

#For Test
add_executable(randomNumberTest ${SOURCE_HEADERS} ${SOURCE_TESTS})

set(ext_libraries ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${sprng_libraries} ${gmp_libraries})
list(REMOVE_DUPLICATES ext_libraries)
target_link_libraries(randomNumberTest randomNumberHao mpiHao testHao libgtest-main-hao ${ext_libraries})

target_include_directories(randomNumberTest PUBLIC ${GTEST_INCLUDE_DIRS})

add_my_test(randomNumberTest "$<TARGET_FILE:randomNumberTest>")