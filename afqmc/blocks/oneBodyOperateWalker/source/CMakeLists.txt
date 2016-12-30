set(SOURCE_FILES
        hoppingOperateSingleDeterminant.cpp)

add_library(afqmcBlocksOneBodyOperateWalerHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcBlocksOneBodyOperateWalerHao STATIC $<TARGET_OBJECTS:afqmcBlocksOneBodyOperateWalerHaoObject>)