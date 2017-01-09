set(SOURCE_FILES
        NiupNidn.cpp
        NiupNidnSample.cpp)

add_library(afqmcNiupNidnHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcNiupNidnHao STATIC $<TARGET_OBJECTS:afqmcNiupNidnHaoObject>)