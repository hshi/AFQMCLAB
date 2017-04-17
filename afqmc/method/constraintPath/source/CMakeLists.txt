set(SOURCE_FILES
        afqmcConstraintPath.cpp
        afqmcConstraintPathMeasure.cpp
        afqmcConstraintPathMethod.cpp
        afqmcConstraintPathProjection.cpp
        afqmcConstraintPathSetWalker.cpp
        AfqmcWalkerPop.cpp)

add_library(afqmcConstraintPathHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcConstraintPathHao STATIC $<TARGET_OBJECTS:afqmcConstraintPathHaoObject>)