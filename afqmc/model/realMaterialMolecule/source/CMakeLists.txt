set(SOURCE_FILES
        realMaterialMolecule.cpp
        realMaterialMoleculeMeasureFixedSD2sSD2is.cpp
        realMaterialMoleculeSD2isOperation.cpp
        realMaterialMoleculeSD2sOperation.cpp )

add_library(afqmcRealMaterialMoleculeHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcRealMaterialMoleculeHao STATIC $<TARGET_OBJECTS:afqmcRealMaterialMoleculeHaoObject>)