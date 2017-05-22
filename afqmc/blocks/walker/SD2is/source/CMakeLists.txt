set(SOURCE_FILES
        SD2is.cpp)

add_library(afqmcSD2isHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcSD2isHao STATIC $<TARGET_OBJECTS:afqmcSD2isHaoObject>)
