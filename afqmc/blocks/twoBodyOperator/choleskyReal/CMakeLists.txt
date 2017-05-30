set(SOURCE_HEADERS
        ${CMAKE_CURRENT_LIST_DIR}/include/choleskyReal.h
        ${CMAKE_CURRENT_LIST_DIR}/include/choleskyRealAux.h
        ${CMAKE_CURRENT_LIST_DIR}/include/choleskyRealForce.h
        ${CMAKE_CURRENT_LIST_DIR}/include/choleskyRealSample.h
        )

add_subdirectory(include)
add_subdirectory(source)
add_subdirectory(test)