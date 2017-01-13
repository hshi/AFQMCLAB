add_subdirectory(walker)
add_subdirectory(oneBodyOperator)
add_subdirectory(twoBodyOperator)
add_subdirectory(walkerWalkerOperation)
add_subdirectory(oneBodyWalkerOperation)
add_subdirectory(twoBodyWalkerOperation)


add_library(afqmcBlocksHao STATIC
        $<TARGET_OBJECTS:afqmcSDHaoObject>

        $<TARGET_OBJECTS:afqmcHopHaoObject>

        $<TARGET_OBJECTS:afqmcNiupNidnHaoObject>

        $<TARGET_OBJECTS:afqmcSDSDOperationHaoObject>

        $<TARGET_OBJECTS:afqmcHopSDOperationHaoObject>

        $<TARGET_OBJECTS:afqmcNiupNidnSDOperationHaoObject>
        )