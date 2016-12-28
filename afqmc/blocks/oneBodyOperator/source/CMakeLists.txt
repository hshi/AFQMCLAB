set(SOURCE_FILES
        hoppingOperator.cpp)

add_library(afqmcBlocksOneBodyOperatorHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcBlocksOneBodyOperatorHao STATIC $<TARGET_OBJECTS:afqmcBlocksOneBodyOperatorHaoObject>)