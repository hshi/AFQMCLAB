set(SOURCE_FILES
        logHop2IS.cpp)

add_library(afqmcLogHop2ISHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcLogHop2ISHao STATIC $<TARGET_OBJECTS:afqmcLogHop2ISHaoObject>)
