add_subdirectory(manipulateMCData)
add_subdirectory(populationControl)

add_library(afqmcUtilitiesHao STATIC
        $<TARGET_OBJECTS:afqmcManipulateMCDataHaoObject>
        $<TARGET_OBJECTS:afqmcPopulationControlHaoObject>
        )

file(RELATIVE_PATH relativeDirectorPath ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_LIST_DIR})
install(FILES utilities.h DESTINATION "include/${relativeDirectorPath}")