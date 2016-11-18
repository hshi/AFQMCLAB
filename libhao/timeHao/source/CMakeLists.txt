set(SOURCE_FILES time_hao.cpp)

add_library(timeHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(timeHao STATIC $<TARGET_OBJECTS:timeHaoObject>)