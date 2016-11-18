set(SOURCE_FILES fullMatrix.cpp)

add_library(lanczosModelFullMatrixHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})

add_library(lanczosModelFullMatrixHao STATIC $<TARGET_OBJECTS:lanczosModelFullMatrixHaoObject>)