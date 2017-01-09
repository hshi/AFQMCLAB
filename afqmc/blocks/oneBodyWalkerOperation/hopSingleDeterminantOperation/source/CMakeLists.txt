set(SOURCE_FILES
        hopSingleDeterminantOperation.cpp)

add_library(afqmcHopSingleDeterminantOperationHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcHopSingleDeterminantOperationHao STATIC $<TARGET_OBJECTS:afqmcHopSingleDeterminantOperationHaoObject>)