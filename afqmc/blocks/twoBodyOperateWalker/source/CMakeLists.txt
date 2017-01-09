set(SOURCE_FILES
        onSiteDensityUpDensityDnOperateSingleDeterminant.cpp)

add_library(afqmcBlocksTwoBodyOperateWalerHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcBlocksTwoBodyOperateWalerHao STATIC $<TARGET_OBJECTS:afqmcBlocksTwoBodyOperateWalerHaoObject>)