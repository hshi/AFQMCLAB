set(SOURCE_FILES brents_fun.cpp simple_fun.cpp polynomialFit.cpp)

add_library(mathHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(mathHao STATIC $<TARGET_OBJECTS:mathHaoObject>)