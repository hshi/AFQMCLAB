set(SOURCE_FILES
        hop.cpp)

add_library(afqmcHopHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcHopHao STATIC $<TARGET_OBJECTS:afqmcHopHaoObject>)