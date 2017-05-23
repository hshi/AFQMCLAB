set(SOURCE_FILES
        SD2sSD2isOperation.cpp)

add_library(afqmcSD2sSD2isOperationHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcSD2sSD2isOperationHao STATIC $<TARGET_OBJECTS:afqmcSD2sSD2isOperationHaoObject>)
