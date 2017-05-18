set(SOURCE_FILES
        hop2SSD2SOperation.cpp)

add_library(afqmcHop2SSD2SOperationHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcHop2SSD2SOperationHao STATIC $<TARGET_OBJECTS:afqmcHop2SSD2SOperationHaoObject>)
