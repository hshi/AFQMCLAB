add_subdirectory(walker)
add_subdirectory(oneBodyOperator)
add_subdirectory(twoBodyOperator)
add_subdirectory(walkerWalkerOperation)
add_subdirectory(oneBodyWalkerOperation)
add_subdirectory(twoBodyWalkerOperation)


add_library(afqmcBlocksHao STATIC
        $<TARGET_OBJECTS:afqmcSDHaoObject>
        $<TARGET_OBJECTS:afqmcSD2sHaoObject>
        $<TARGET_OBJECTS:afqmcSD2isHaoObject>

        $<TARGET_OBJECTS:afqmcHopHaoObject>
        $<TARGET_OBJECTS:afqmcHop2sHaoObject>
        $<TARGET_OBJECTS:afqmcHop2isHaoObject>
        $<TARGET_OBJECTS:afqmcLogHop2isHaoObject>

        $<TARGET_OBJECTS:afqmcNiupNidnHaoObject>

        $<TARGET_OBJECTS:afqmcSDSDOperationHaoObject>
        $<TARGET_OBJECTS:afqmcSD2sSD2isOperationHaoObject>

        $<TARGET_OBJECTS:afqmcHopSDOperationHaoObject>
        $<TARGET_OBJECTS:afqmcHop2sSD2sOperationHaoObject>
        $<TARGET_OBJECTS:afqmcHop2isSD2isOperationHaoObject>
        $<TARGET_OBJECTS:afqmcLogHop2isSD2isOperationHaoObject>

        $<TARGET_OBJECTS:afqmcNiupNidnSDOperationHaoObject>
        )

file(RELATIVE_PATH relativeDirectorPath ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_LIST_DIR})
install(FILES blocks.h DESTINATION "include/${relativeDirectorPath}")
