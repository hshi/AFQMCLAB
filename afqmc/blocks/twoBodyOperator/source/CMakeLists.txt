set(SOURCE_FILES
        densityDensityOperator.cpp
        onSiteDensityUpDensityDnOperator.cpp)

add_library(afqmcBlocksTwoBodyOperatorHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcBlocksTwoBodyOperatorHao STATIC $<TARGET_OBJECTS:afqmcBlocksTwoBodyOperatorHaoObject>)