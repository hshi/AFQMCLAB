set(SOURCE_FILES
        SD2S.cpp)

add_library(afqmcSD2SHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcSD2SHao STATIC $<TARGET_OBJECTS:afqmcSD2SHaoObject>)
