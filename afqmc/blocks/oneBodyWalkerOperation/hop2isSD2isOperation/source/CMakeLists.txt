set(SOURCE_FILES
        hop2isSD2isOperation.cpp)

add_library(afqmcHop2isSD2isOperationHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcHop2isSD2isOperationHao STATIC $<TARGET_OBJECTS:afqmcHop2isSD2isOperationHaoObject>)
