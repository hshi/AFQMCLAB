set(SOURCE_FILES
        SD.cpp)

add_library(afqmcSDHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcSDHao STATIC $<TARGET_OBJECTS:afqmcSDHaoObject>)