set(SOURCE_FILES hdf5CustomHao.cpp)

add_library(hdf5CustomHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(hdf5CustomHao STATIC $<TARGET_OBJECTS:hdf5CustomHaoObject>)