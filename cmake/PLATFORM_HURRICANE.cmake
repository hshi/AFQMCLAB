set(CMAKE_CXX_COMPILER mpicxx)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3 -march=corei7 -m64 -DNDEBUG")

set(MPIEXEC mvp2run)

set(MPIEXEC_NUMPROC_FLAG "-c")

add_definitions(-DMPI_HAO)