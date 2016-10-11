#For source
set(SOURCE_HEADERS mpi_fun.h)
set(SOURCE_FILES mpi_fun.cpp)
set(SOURCE_TESTS mpi_fun_test.cpp)

#For library
add_library(mpiHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(mpiHao STATIC $<TARGET_OBJECTS:mpiHaoObject>)

#For Test
add_executable(mpiTest ${SOURCE_HEADERS} ${SOURCE_TESTS})
target_link_libraries(mpiTest mpiHao testHao libgtest-main-hao ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(mpiTest PUBLIC ${GTEST_INCLUDE_DIRS})
add_my_test(mpiTest "$<TARGET_FILE:mpiTest>")