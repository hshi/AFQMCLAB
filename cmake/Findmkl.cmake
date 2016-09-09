#Try to find mkl
find_library(lp64_libraries NAMES mkl_intel_lp64 HINTS "$ENV{MKL}/lib/intel64" "$ENV{MKLHOME}/lib/intel64")
find_library(core_libraries NAMES mkl_core HINTS "$ENV{MKL}/lib/intel64" "$ENV{MKLHOME}/lib/intel64")
find_library(sequential_libraries NAMES mkl_sequential HINTS "$ENV{MKL}/lib/intel64" "$ENV{MKLHOME}/lib/intel64")
set(mkl_libraries ${lp64_libraries} ${core_libraries} ${sequential_libraries} m dl pthread)

find_path(mkl_include_dirs mkl.h HINTS "$ENV{MKL}/include" "$ENV{MKLHOME}/include")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(mkl  DEFAULT_MSG
                                  mkl_libraries mkl_include_dirs)
mark_as_advanced(mkl_include_dirs mkl_libraries)
set(mkl_flags "")

if(NOT MKL_FOUND)
  MESSAGE ("-- In order to find mkl, please define MKL or MKLHOME, MKL='/path/to/mkl' ")
endif()
