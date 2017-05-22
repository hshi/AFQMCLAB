set(SOURCE_FILES
        logHop2isSD2isOperation.cpp)

add_library(afqmcLogHop2isSD2isOperationHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcLogHop2isSD2isOperationHao STATIC $<TARGET_OBJECTS:afqmcLogHop2isSD2isOperationHaoObject>)
