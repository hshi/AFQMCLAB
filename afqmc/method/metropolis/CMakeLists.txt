set(SOURCE_HEADERS
        ${CMAKE_CURRENT_LIST_DIR}/include/afqmcMetropolis.h
        ${CMAKE_CURRENT_LIST_DIR}/include/afqmcMetropolisMethod.h
        )

add_subdirectory(include)
add_subdirectory(source)
add_subdirectory(test)