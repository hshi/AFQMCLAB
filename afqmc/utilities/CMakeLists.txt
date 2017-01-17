add_subdirectory(manipulateMCData)

add_library(afqmcUtilitiesHao STATIC
        $<TARGET_OBJECTS:afqmcManipulateMCDataHaoObject>
        )

file(RELATIVE_PATH relativeDirectorPath ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_LIST_DIR})
install(FILES utilities.h DESTINATION "include/${relativeDirectorPath}")