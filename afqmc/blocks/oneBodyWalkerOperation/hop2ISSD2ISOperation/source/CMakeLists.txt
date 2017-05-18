set(SOURCE_FILES
        hop2ISSD2ISOperation.cpp)

add_library(afqmcHop2ISSD2ISOperationHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcHop2ISSD2ISOperationHao STATIC $<TARGET_OBJECTS:afqmcHop2ISSD2ISOperationHaoObject>)
