set(CMAKE_CXX_COMPILER mpicxx)

set(MPIEXEC ibrun)

set(MPIEXEC_NUMPROC_FLAG "-n")

set(EXT_DEFINITIONS "-DMPI_HAO" ${EXT_DEFINITIONS})

set(EXT_FLAGS "-Wall -O3 -xHOST -DNDEBUG ${EXT_FLAGS}")