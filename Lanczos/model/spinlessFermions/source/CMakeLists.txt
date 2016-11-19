set(SOURCE_FILES SpinlessFermions.cpp)

add_library(lanczosModelSpinlessFermionsHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})

add_library(lanczosModelSpinlessFermionsHao STATIC $<TARGET_OBJECTS:lanczosModelSpinlessFermionsHaoObject>)