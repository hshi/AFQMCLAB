set(EXT_INCLUDE_DIRS ${GTEST_INCLUDE_DIRS} ${EXT_INCLUDE_DIRS})
set(EXT_LIBRARIES ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${EXT_LIBRARIES})

set(EXT_LIBRARIES ${gmp_libraries} ${EXT_LIBRARIES})

set(EXT_DEFINITIONS ${sprng_definitions} ${EXT_DEFINITIONS} )
set(EXT_INCLUDE_DIRS ${sprng_include_dirs} ${EXT_INCLUDE_DIRS})
set(EXT_LIBRARIES ${sprng_libraries} ${EXT_LIBRARIES})

set(EXT_INCLUDE_DIRS ${fftw_include_dirs} ${EXT_INCLUDE_DIRS})
set(EXT_LIBRARIES ${fftw_libraries} ${EXT_LIBRARIES})

set(EXT_DEFINITIONS ${lapackblas_definitions} ${EXT_DEFINITIONS})
set(EXT_FLAGS "${lapackblas_flags} ${EXT_FLAGS}")
set(EXT_INCLUDE_DIRS ${lapackblas_include_dirs} ${EXT_INCLUDE_DIRS})
set(EXT_LIBRARIES ${lapackblas_libraries} ${EXT_LIBRARIES})

set(EXT_DEFINITIONS ${openmp_definitions} ${EXT_DEFINITIONS})
set(EXT_FLAGS "${openmp_flags} ${EXT_FLAGS}")

set(EXT_DEFINITIONS ${int64_definitions} ${EXT_DEFINITIONS})

#Remove Duplication
list(REMOVE_DUPLICATES EXT_DEFINITIONS)
removeDuplicateSubstring(${EXT_FLAGS} EXT_FLAGS)
list(REMOVE_DUPLICATES EXT_INCLUDE_DIRS)
list(REMOVE_DUPLICATES EXT_LIBRARIES)

add_definitions(${EXT_DEFINITIONS})
include_directories(${EXT_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EXT_FLAGS}")
removeDuplicateSubstring(${CMAKE_CXX_FLAGS} CMAKE_CXX_FLAGS)