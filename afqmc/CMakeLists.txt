add_subdirectory(utilities)
add_subdirectory(blocks)
add_subdirectory(model)

add_library(afqmcHao STATIC
        #utilities
        $<TARGET_OBJECTS:afqmcManipulateMCDataHaoObject>
        $<TARGET_OBJECTS:afqmcPopulationControlHaoObject>

        #Blocks
        $<TARGET_OBJECTS:afqmcSDHaoObject>
        $<TARGET_OBJECTS:afqmcSD2SHaoObject>
        $<TARGET_OBJECTS:afqmcSD2ISHaoObject>

        $<TARGET_OBJECTS:afqmcHopHaoObject>
        $<TARGET_OBJECTS:afqmcHop2SHaoObject>
        $<TARGET_OBJECTS:afqmcHop2ISHaoObject>

        $<TARGET_OBJECTS:afqmcNiupNidnHaoObject>

        $<TARGET_OBJECTS:afqmcSDSDOperationHaoObject>

        $<TARGET_OBJECTS:afqmcHopSDOperationHaoObject>
        $<TARGET_OBJECTS:afqmcHop2SSD2SOperationHaoObject>
        $<TARGET_OBJECTS:afqmcHop2ISSD2ISOperationHaoObject>

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
