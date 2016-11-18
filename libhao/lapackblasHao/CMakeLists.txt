set(SOURCE_HEADERS Hao_types.h customized_blas.h customized_lapack.h blas_lapack_wrap.h)

file(RELATIVE_PATH relativeDirectorPath ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_LIST_DIR})
install(FILES ${SOURCE_HEADERS} DESTINATION "include/${relativeDirectorPath}")