set(SOURCE_FILES
        SDSDOperation.cpp)

add_library(afqmcSDSDOperationHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcSDSDOperationHao STATIC $<TARGET_OBJECTS:afqmcSDSDOperationHaoObject>)