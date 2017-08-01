if(USE_OPENMP)
    set(openmp_definitions "-DUSE_OPENMP")
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        set(openmp_flags "-fopenmp")
    elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
        set(openmp_flags "-qopenmp")
    elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "PGI")
        set(openmp_flags "-mp -pgf90libs")
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(openmp_flags "-fopenmp")
        message("-- WARNING!!! In my Mac, Clang does not support openmp! Recommend to use Intel or GNU compiler!")
    endif()
endif()

if(USE_INT64)
    set(int64_definitions "-DUSE_INT64")
endif()