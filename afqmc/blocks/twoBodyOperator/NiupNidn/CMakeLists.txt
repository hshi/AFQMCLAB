set(SOURCE_HEADERS
        ${CMAKE_CURRENT_LIST_DIR}/include/NiupNidn.h
        ${CMAKE_CURRENT_LIST_DIR}/include/NiupNidnAux.h
        ${CMAKE_CURRENT_LIST_DIR}/include/NiupNidnForce.h
        ${CMAKE_CURRENT_LIST_DIR}/include/NiupNidnSample.h
        )

add_subdirectory(include)
add_subdirectory(source)
add_subdirectory(test)