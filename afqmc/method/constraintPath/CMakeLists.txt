set(SOURCE_HEADERS
        ${CMAKE_CURRENT_LIST_DIR}/include/afqmcConstraintPath.h
        ${CMAKE_CURRENT_LIST_DIR}/include/afqmcConstraintPathDefine.h
        ${CMAKE_CURRENT_LIST_DIR}/include/afqmcConstraintPathMethod.h
        ${CMAKE_CURRENT_LIST_DIR}/include/afqmcWalkerPop.h
        )

add_subdirectory(include)
add_subdirectory(source)
add_subdirectory(test)
