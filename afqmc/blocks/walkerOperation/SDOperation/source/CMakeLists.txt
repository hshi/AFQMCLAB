set(SOURCE_FILES
        SDOperation.cpp)

add_library(afqmcSDOperationHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcSDOperationHao STATIC $<TARGET_OBJECTS:afqmcSDOperationHaoObject>)