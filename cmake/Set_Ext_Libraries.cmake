set(ext_definitions "")
set(ext_flags "")
set(ext_include_dirs "")
set(ext_libraries "")

set(ext_include_dirs ${GTEST_INCLUDE_DIRS} ${ext_include_dirs})
set(ext_libraries ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${ext_libraries})

set(ext_libraries ${gmp_libraries} ${ext_libraries})

set(ext_definitions ${sprng_definitions} ${ext_definitions} )
set(ext_include_dirs ${sprng_include_dirs} ${ext_include_dirs})
set(ext_libraries ${sprng_libraries} ${ext_libraries})

set(ext_include_dirs ${fftw_include_dirs} ${ext_include_dirs})
set(ext_libraries ${fftw_libraries} ${ext_libraries})

set(ext_definitions ${lapackblas_definitions} ${ext_definitions})
set(ext_flags "${lapackblas_flags} ${ext_flags}")
set(ext_include_dirs ${lapackblas_include_dirs} ${ext_include_dirs})
set(ext_libraries ${lapackblas_libraries} ${ext_libraries})

set(ext_flags "${openmp_flags} ${ext_flags}")

list(REMOVE_DUPLICATES ext_libraries)
