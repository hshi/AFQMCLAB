set(SOURCE_FILES
        SD2s.cpp)

add_library(afqmcSD2sHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcSD2sHao STATIC $<TARGET_OBJECTS:afqmcSD2sHaoObject>)
