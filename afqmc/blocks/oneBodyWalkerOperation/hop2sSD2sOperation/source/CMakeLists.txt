set(SOURCE_FILES
        hop2sSD2sOperation.cpp)

add_library(afqmcHop2sSD2sOperationHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcHop2sSD2sOperationHao STATIC $<TARGET_OBJECTS:afqmcHop2sSD2sOperationHaoObject>)
