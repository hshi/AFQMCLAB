set(SOURCE_FILES cluster.cpp supercubic.cpp)

add_library(latticeHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})

add_library(latticeHao STATIC $<TARGET_OBJECTS:latticeHaoObject>)