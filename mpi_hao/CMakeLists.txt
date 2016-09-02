set(SOURCE_HEADERS include/mpi_fun.h)

set(SOURCE_FILES source/mpi_fun.cpp)

set(SOURCE_TESTS test/mpi_fun_test.cpp test/test_all.cpp)

add_library(mpihao OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})

add_executable(mpitest ${SOURCE_HEADERS} ${SOURCE_TESTS} $<TARGET_OBJECTS:mpihao>)