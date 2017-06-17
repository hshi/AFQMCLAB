set(SOURCE_FILES
        realMaterialMolecule.cpp
        realMaterialMoleculeFixedSD2sSD2is.cpp)

add_library(afqmcRealMaterialMoleculeHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcRealMaterialMoleculeHao STATIC $<TARGET_OBJECTS:afqmcRealMaterialMoleculeHaoObject>)