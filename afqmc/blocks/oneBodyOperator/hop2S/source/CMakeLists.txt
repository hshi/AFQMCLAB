set(SOURCE_FILES
        hop2S.cpp)

add_library(afqmcHop2SHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcHop2SHao STATIC $<TARGET_OBJECTS:afqmcHop2SHaoObject>)
