set(SOURCE_FILES
        afqmcPhaselessMethod.cpp
        afqmcPhaseless.cpp
        afqmcPhaselessProjection.cpp
        afqmcPhaselessSetWalker.cpp
        afqmcPhaselessMeasure.cpp
        afqmcWalkerPop.cpp
        )

add_library(afqmcPhaselessHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcPhaselessHao STATIC $<TARGET_OBJECTS:afqmcPhaselessHaoObject>)