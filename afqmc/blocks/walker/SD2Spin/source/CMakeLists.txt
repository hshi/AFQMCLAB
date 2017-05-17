set(SOURCE_FILES
        SD2Spin.cpp)

add_library(afqmcSD2SpinHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(afqmcSD2SpinHao STATIC $<TARGET_OBJECTS:afqmcSD2SpinHaoObject>)