set(SOURCE_FILES SpinlessFermions.cpp SpinlessFermionsReadWrite.cpp SpinlessFermionsOperation.cpp)

add_library(lanczosModelSpinlessFermionsHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})

add_library(lanczosModelSpinlessFermionsHao STATIC $<TARGET_OBJECTS:lanczosModelSpinlessFermionsHaoObject>)