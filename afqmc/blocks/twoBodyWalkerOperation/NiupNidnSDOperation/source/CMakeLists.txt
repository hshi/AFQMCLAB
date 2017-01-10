set(SOURCE_FILES
        NiupNidnSDOperation.cpp)

add_library(afqmcNiupNidnSDOperationHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcNiupNidnSDOperationHao STATIC $<TARGET_OBJECTS:afqmcNiupNidnSDOperationHaoObject>)