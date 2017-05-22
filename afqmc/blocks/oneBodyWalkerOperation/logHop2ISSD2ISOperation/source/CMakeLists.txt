set(SOURCE_FILES
        logHop2ISSD2ISOperation.cpp)

add_library(afqmcLogHop2ISSD2ISOperationHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcLogHop2ISSD2ISOperationHao STATIC $<TARGET_OBJECTS:afqmcLogHop2ISSD2ISOperationHaoObject>)
