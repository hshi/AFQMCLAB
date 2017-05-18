set(SOURCE_FILES
        hop2IS.cpp)

add_library(afqmcHop2ISHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcHop2ISHao STATIC $<TARGET_OBJECTS:afqmcHop2ISHaoObject>)
