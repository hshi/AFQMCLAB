set(SOURCE_FILES
        singleDeterminant.cpp)

add_library(afqmcSingleDeterminantHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcSingleDeterminantHao STATIC $<TARGET_OBJECTS:afqmcSingleDeterminantHaoObject>)