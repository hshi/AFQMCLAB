set(SOURCE_FILES fftw_hao.cpp)

add_library(fftwHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(fftwHao STATIC $<TARGET_OBJECTS:fftwHaoObject>)