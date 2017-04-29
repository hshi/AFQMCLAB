set(SOURCE_HEADERS
        ${CMAKE_CURRENT_LIST_DIR}/include/brents_fun.h
        ${CMAKE_CURRENT_LIST_DIR}/include/simple_fun.h
        ${CMAKE_CURRENT_LIST_DIR}/include/sort_fun.h
        ${CMAKE_CURRENT_LIST_DIR}/include/polynomialFit.h
        ${CMAKE_CURRENT_LIST_DIR}/include/math_container.h)

add_subdirectory(include)
add_subdirectory(source)
add_subdirectory(test)