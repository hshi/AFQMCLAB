set(HintLibraryPath "$ENV{ACML}/lib64" "$ENV{ACML}/lib" "$ENV{ACMLHOME}/lib64" "$ENV{ACMLHOME}/lib")
set(HintIncludePath "$ENV{ACML}/include" "$ENV{ACMLHOME}/include")

if(USE_OPENMP)
    set(acml_name libacml_mp.a)
else()
    set(acml_name libacml.a)
endif()

find_library(acml_libraries NAMES ${acml_name} HINTS ${HintLibraryPath})
find_path(acml_include_dirs acml.h HINTS ${HintIncludePath})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(acml  DEFAULT_MSG
                                  acml_libraries acml_include_dirs)
mark_as_advanced(acml_include_dirs acml_libraries)

if(NOT ACML_FOUND)
  MESSAGE ("-- In order to find acml, please define ACML or ACMLHOME, ACML='/path/to/acml' ")
endif()