set(SOURCE_FILES
        SD2IS.cpp)

add_library(afqmcSD2ISHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcSD2ISHao STATIC $<TARGET_OBJECTS:afqmcSD2ISHaoObject>)
