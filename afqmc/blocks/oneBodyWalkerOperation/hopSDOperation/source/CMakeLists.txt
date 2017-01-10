set(SOURCE_FILES
        hopSDOperation.cpp)

add_library(afqmcHopSDOperationHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcHopSDOperationHao STATIC $<TARGET_OBJECTS:afqmcHopSDOperationHaoObject>)