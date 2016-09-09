#Try to find acml
find_library(acml_libraries NAMES libacml.a libacml_mp.a HINTS "$ENV{ACML}/lib64" "$ENV{ACML}/lib" "$ENV{ACMLHOME}/lib64" "$ENV{ACMLHOME}/lib")
find_path(acml_include_dirs acml.h HINTS "$ENV{ACML}/include" "$ENV{ACMLHOME}/include")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(acml  DEFAULT_MSG
                                  acml_libraries acml_include_dirs)
mark_as_advanced(acml_include_dirs acml_libraries)

if(NOT ACML_FOUND)
  MESSAGE ("-- In order to find acml, please define ACML or ACMLHOME, ACML='/path/to/acml' ")
endif()
