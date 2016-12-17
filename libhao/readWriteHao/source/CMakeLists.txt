set(SOURCE_FILES readWriteHao.cpp)

add_library(readWriteHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(readWriteHao STATIC $<TARGET_OBJECTS:readWriteHaoObject>)