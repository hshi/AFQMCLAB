set(SOURCE_FILES
        afqmcMetropolis.cpp
        afqmcMetropolisMethod.cpp)

add_library(afqmcMetropolisHubbardSDSDHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcMetropolisHubbardSDSDHao STATIC $<TARGET_OBJECTS:afqmcMetropolisHubbardSDSDHaoObject>)