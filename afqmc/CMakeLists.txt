add_subdirectory(utilities)
add_subdirectory(blocks)
add_subdirectory(model)

add_library(afqmcHao STATIC
        #utilities
        $<TARGET_OBJECTS:afqmcManipulateMCDataHaoObject>
        $<TARGET_OBJECTS:afqmcPopulationControlHaoObject>

        #Blocks
        $<TARGET_OBJECTS:afqmcSDHaoObject>
        $<TARGET_OBJECTS:afqmcSD2sHaoObject>
        $<TARGET_OBJECTS:afqmcSD2isHaoObject>

        $<TARGET_OBJECTS:afqmcHopHaoObject>
        $<TARGET_OBJECTS:afqmcHop2sHaoObject>
        $<TARGET_OBJECTS:afqmcHop2isHaoObject>
        $<TARGET_OBJECTS:afqmcLogHop2isHaoObject>

        $<TARGET_OBJECTS:afqmcNiupNidnHaoObject>
        $<TARGET_OBJECTS:afqmcCholeskyRealHaoObject>

        $<TARGET_OBJECTS:afqmcSDSDOperationHaoObject>
        $<TARGET_OBJECTS:afqmcSD2sSD2isOperationHaoObject>

        $<TARGET_OBJECTS:afqmcHopSDOperationHaoObject>
        $<TARGET_OBJECTS:afqmcHop2sSD2sOperationHaoObject>
        $<TARGET_OBJECTS:afqmcHop2isSD2isOperationHaoObject>
        $<TARGET_OBJECTS:afqmcLogHop2isSD2isOperationHaoObject>

        $<TARGET_OBJECTS:afqmcNiupNidnSDOperationHaoObject>

        #model
        $<TARGET_OBJECTS:afqmcHubbardRealSpaceSOCHaoObject>
        $<TARGET_OBJECTS:afqmcRealMaterialMoleculeHaoObject>
        )

install(TARGETS afqmcHao DESTINATION lib EXPORT afqmcHaoTargets)
install(EXPORT afqmcHaoTargets DESTINATION cmake)

file(RELATIVE_PATH relativeDirectorPath ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_LIST_DIR})
install(FILES afqmc.h DESTINATION "include/${relativeDirectorPath}")

#For Tutorial
add_subdirectory(method)
