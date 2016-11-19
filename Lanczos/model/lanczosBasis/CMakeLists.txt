set(SOURCE_HEADERS
        ${CMAKE_CURRENT_LIST_DIR}/include/lanczosBasis.h
        ${CMAKE_CURRENT_LIST_DIR}/include/lanczosOperators.h)

add_subdirectory(include)
add_subdirectory(source)
add_subdirectory(test)