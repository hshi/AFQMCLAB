set(SOURCE_HEADERS
        ${CMAKE_CURRENT_LIST_DIR}/include/cluster.h
        ${CMAKE_CURRENT_LIST_DIR}/include/supercubic.h
        ${CMAKE_CURRENT_LIST_DIR}/include/latticeAll.h)

add_subdirectory(include)
add_subdirectory(source)
add_subdirectory(test)