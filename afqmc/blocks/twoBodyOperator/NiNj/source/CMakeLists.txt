set(SOURCE_FILES
        NiNj.cpp)

add_library(afqmcNiNjHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcNiNjHao STATIC $<TARGET_OBJECTS:afqmcNiNjHaoObject>)