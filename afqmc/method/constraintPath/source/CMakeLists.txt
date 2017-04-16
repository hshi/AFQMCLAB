set(SOURCE_FILES
        afqmcConstraintPathMethod.cpp
        afqmcConstraintPath.cpp)

add_library(afqmcConstraintPathHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcConstraintPathHao STATIC $<TARGET_OBJECTS:afqmcConstraintPathHaoObject>)