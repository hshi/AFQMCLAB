find_package(MPI REQUIRED)

set(CMAKE_CXX_COMPILER ${MPI_CXX_COMPILER})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3")

add_definitions(-DMPI_HAO)

#FindMPI.cmake will define MPIEXEC and MPIEXEC_NUMPROC_FLAG