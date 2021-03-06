set(HintLibraryPath "$ENV{FFTW}/lib" "$ENV{FFTWHOME}/lib")
set(HintIncludePath "$ENV{FFTW}/include" "$ENV{FFTWHOME}/include")

find_library(fftw_libraries NAMES libfftw3.a HINTS ${HintLibraryPath})
find_path(fftw_include_dirs fftw3.h HINTS ${HintIncludePath})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(fftw  DEFAULT_MSG
                                  fftw_libraries fftw_include_dirs)
mark_as_advanced(fftw_include_dirs fftw_libraries)

if(NOT FFTW_FOUND)
  MESSAGE ("-- In order to find fftw, please define FFTW or FFTWHOME, FFTW='/path/to/fftw' ")
endif()
