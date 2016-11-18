set(SOURCE_FILES random_hao.cpp)

add_library(randomNumberHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(randomNumberHao STATIC $<TARGET_OBJECTS:randomNumberHaoObject>)