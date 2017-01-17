add_subdirectory(utilities)
add_subdirectory(blocks)
add_subdirectory(model)

add_library(afqmcHao STATIC
        #utilities
        $<TARGET_OBJECTS:afqmcManipulateMCDataHaoObject>

        #Blocks
        $<TARGET_OBJECTS:afqmcSDHaoObject>

        $<TARGET_OBJECTS:afqmcHopHaoObject>

        $<TARGET_OBJECTS:afqmcNiupNidnHaoObject>

        $<TARGET_OBJECTS:afqmcSDSDOperationHaoObject>

        $<TARGET_OBJECTS:afqmcHopSDOperationHaoObject>

        $<TARGET_OBJECTS:afqmcNiupNidnSDOperationHaoObject>

        #model
        $<TARGET_OBJECTS:afqmcHubbardRealSpaceSOCHaoObject>
        )

install(TARGETS afqmcHao DESTINATION lib EXPORT afqmcHaoTargets)
install(EXPORT afqmcHaoTargets DESTINATION cmake)

file(RELATIVE_PATH relativeDirectorPath ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_LIST_DIR})
install(FILES afqmc.h DESTINATION "include/${relativeDirectorPath}")

#For Tutorial
add_subdirectory(method)