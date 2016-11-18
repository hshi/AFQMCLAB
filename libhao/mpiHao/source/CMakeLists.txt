set(SOURCE_FILES mpi_fun.cpp)

add_library(mpiHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(mpiHao STATIC $<TARGET_OBJECTS:mpiHaoObject>)