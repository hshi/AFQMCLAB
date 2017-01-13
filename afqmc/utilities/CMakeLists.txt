add_subdirectory(manipulateMCData)

add_library(afqmcUtilitiesHao STATIC
        $<TARGET_OBJECTS:afqmcManipulateMCDataHaoObject>
        )