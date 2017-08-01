set(SOURCE_FILES
        HubbardSOC.cpp
        HubbardSOCSDOperation.cpp
        HubbardSOCMeasureFixedSDSD.cpp
        HubbardSOCMeasureCommuteSDSD.cpp
        HubbardSOCMeasureObserveSDSD.cpp)

add_library(afqmcHubbardRealSpaceSOCHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcHubbardRealSpaceSOCHao STATIC $<TARGET_OBJECTS:afqmcHubbardRealSpaceSOCHaoObject>)