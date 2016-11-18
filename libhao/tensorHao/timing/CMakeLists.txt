set(SOURCE_TIMING bl_cpu_magma_timing.cpp timing_all.cpp)

add_executable(tensorTiming ${SOURCE_HEADERS} ${SOURCE_TIMING})

target_link_libraries(tensorTiming tensorHao mpiHao ${EXT_LIBRARIES})

install(TARGETS tensorTiming DESTINATION timing)