set(SOURCE_FILES
        singleDeterminant.cpp)

add_library(afqmcBlocksWalkerHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcBlocksWalkerHao STATIC $<TARGET_OBJECTS:afqmcBlocksWalkerHaoObject>)