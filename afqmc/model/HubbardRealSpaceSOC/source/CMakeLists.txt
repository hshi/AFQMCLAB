set(SOURCE_FILES
        HubbardSOC.cpp
        HubbardSOCMeasureCommuteSDSD.cpp
        HubbardSOCMeasureFixedSDSD.cpp
        HubbardSOCMeasureObserveSDSD.cpp
        HubbardSOCSDOperation.cpp)

add_library(afqmcHubbardRealSpaceSOCHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcHubbardRealSpaceSOCHao STATIC $<TARGET_OBJECTS:afqmcHubbardRealSpaceSOCHaoObject>)