set(SOURCE_FILES
        HubbardRealSpaceSOC.cpp)

add_library(afqmcHubbardRealSpaceSOCHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcHubbardRealSpaceSOCHao STATIC $<TARGET_OBJECTS:afqmcHubbardRealSpaceSOCHaoObject>)