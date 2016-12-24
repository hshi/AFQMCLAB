set(SOURCE_FILES
        realMaterial.cpp
        realMaterialReadWrite.cpp
        realMaterialSetup.cpp
        realMaterialOperation.cpp)

add_library(lanczosModelRealMaterialHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})

add_library(lanczosModelRealMaterialHao STATIC $<TARGET_OBJECTS:lanczosModelRealMaterialHaoObject>)