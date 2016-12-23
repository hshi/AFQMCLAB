set(SOURCE_FILES
        tensor_1d_bl_cpu.cpp
        tensor_2d_bl_cpu.cpp
        tensor_2d_bl_magma.cpp
        tensor_2d_common_fun.cpp
        tensor_fill.cpp)

add_library(tensorHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(tensorHao STATIC $<TARGET_OBJECTS:tensorHaoObject>)