set(HintLibraryPath "$ENV{MAGMA}/lib64" "$ENV{MAGMA}/lib" "$ENV{MAGMAHOME}/lib64" "$ENV{MAGMAHOME}/lib")
set(HintIncludePath "$ENV{MAGMA}/include" "$ENV{MAGMAHOME}/include")

find_library(magma_libraries NAMES libmagma.so libmagma.a HINTS ${HintLibraryPath} )
find_path(magma_include_dirs magma.h HINTS ${HintIncludePath})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(magma  DEFAULT_MSG
                                  magma_libraries magma_include_dirs)
mark_as_advanced(magma_include_dirs magma_libraries)

if(NOT MAGMA_FOUND)
  MESSAGE ("-- In order to find MAGMA, please define MAGMA or MAGMAHOME, MAGMA='/path/to/magma'")
endif()
