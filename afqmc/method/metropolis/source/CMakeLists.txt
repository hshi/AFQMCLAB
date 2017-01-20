set(SOURCE_FILES
        afqmcMetropolis.cpp
        afqmcMetropolisMeasure.cpp
        afqmcMetropolisSetWalkerAndField.cpp
        afqmcMetropolisMethod.cpp
        afqmcMetropolisUpdate.cpp)

add_library(afqmcMetropolisHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcMetropolisHao STATIC $<TARGET_OBJECTS:afqmcMetropolisHaoObject>)