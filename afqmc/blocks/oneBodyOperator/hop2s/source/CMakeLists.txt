set(SOURCE_FILES
        hop2s.cpp)

add_library(afqmcHop2sHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcHop2sHao STATIC $<TARGET_OBJECTS:afqmcHop2sHaoObject>)
