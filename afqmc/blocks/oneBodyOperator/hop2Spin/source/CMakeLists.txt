set(SOURCE_FILES
        hop2Spin.cpp)

add_library(afqmcHop2SpinHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcHop2SpinHao STATIC $<TARGET_OBJECTS:afqmcHop2SpinHaoObject>)