set(SOURCE_FILES
        choleskyReal.cpp)

add_library(afqmcCholeskyRealHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcCholeskyRealHao STATIC $<TARGET_OBJECTS:afqmcCholeskyRealHaoObject>)