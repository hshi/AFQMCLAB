#For souce
set(SOURCE_HEADERS include/mpi_fun.h)

set(SOURCE_FILES source/mpi_fun.cpp)

set(SOURCE_TESTS test/mpi_fun_test.cpp)


#For library
add_library(mpihao OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})


#For Test
add_executable(mpitest ${SOURCE_HEADERS} $<TARGET_OBJECTS:mpihao> ${SOURCE_TESTS})

target_link_libraries(mpitest libgtest-main-hao ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

target_include_directories(mpitest PUBLIC ${GTEST_INCLUDE_DIRS})

add_test(mpitest mpirun -np 4 mpitest)