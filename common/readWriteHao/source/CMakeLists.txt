set(SOURCE_FILES readWriteStringFile.cpp readWriteHdf5.cpp readBySearchString.cpp)

add_library(readWriteHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(readWriteHao STATIC $<TARGET_OBJECTS:readWriteHaoObject>)