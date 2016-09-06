#Try to find gmp
find_library(gmp_libraries NAMES libgmp.a HINTS "$ENV{GMP}/lib" "$ENV{GMPHOME}/lib")
find_path(gmp_include_dirs gmp.h HINTS "$ENV{GMP}/include" "$ENV{GMPHOME}/include")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(gmp  DEFAULT_MSG
                                  gmp_libraries gmp_include_dirs)
mark_as_advanced(gmp_include_dirs gmp_libraries)

if(NOT GMP_FOUND)
  MESSAGE ("-- In order to find gmp, please define GMP or GMPHOME, GMP='/path/to/gmp' ")
endif()
