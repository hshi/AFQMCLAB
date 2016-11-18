set(SOURCE_FILES lanczosBasis.cpp)

add_library(lanczosBasisHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})

add_library(lanczosBasisHao STATIC $<TARGET_OBJECTS:lanczosBasisHaoObject>)