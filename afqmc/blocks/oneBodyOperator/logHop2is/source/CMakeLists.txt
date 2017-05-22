set(SOURCE_FILES
        logHop2is.cpp)

add_library(afqmcLogHop2isHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcLogHop2isHao STATIC $<TARGET_OBJECTS:afqmcLogHop2isHaoObject>)
