set(SOURCE_FILES
        hop2is.cpp)

add_library(afqmcHop2isHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcHop2isHao STATIC $<TARGET_OBJECTS:afqmcHop2isHaoObject>)
