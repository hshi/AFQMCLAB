set(SOURCE_FILES
        populationControlAux.cpp
        populationControlConfiguration.cpp)

add_library(afqmcPopulationControlHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcPopulationControlHao STATIC $<TARGET_OBJECTS:afqmcPopulationControlHaoObject>)