set(SOURCE_HEADERS
        ${CMAKE_CURRENT_LIST_DIR}/include/afqmcPhaselessDefine.h
        ${CMAKE_CURRENT_LIST_DIR}/include/afqmcPhaselessMethod.h
        ${CMAKE_CURRENT_LIST_DIR}/include/afqmcWalkerPop.h
        ${CMAKE_CURRENT_LIST_DIR}/include/afqmcPhaseless.h
        )

add_subdirectory(include)
add_subdirectory(source)
add_subdirectory(test)