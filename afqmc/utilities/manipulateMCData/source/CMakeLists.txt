set(SOURCE_FILES
        writeThreadSum.cpp)

add_library(afqmcManipulateMCDataHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcManipulateMCDataHao STATIC $<TARGET_OBJECTS:afqmcManipulateMCDataHaoObject>)