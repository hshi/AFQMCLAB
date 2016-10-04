#For source
set(SOURCE_HEADERS fftw_hao.h)
set(SOURCE_FILES fftw_hao.cpp)
set(SOURCE_TESTS fftw_hao_test.cpp)

#For FFTW
include_directories(${fftw_include_dirs})

#For library
add_library(fftwHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(fftwHao STATIC $<TARGET_OBJECTS:fftwHaoObject>)

#For Test
add_executable(fftwTest ${SOURCE_HEADERS} ${SOURCE_TESTS})

set(ext_libraries ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${fftw_libraries})
list(REMOVE_DUPLICATES ext_libraries)
target_link_libraries(fftwTest fftwHao mpiHao testHao libgtest-main-hao ${ext_libraries})

target_include_directories(fftwTest PUBLIC ${GTEST_INCLUDE_DIRS})

add_my_test(fftwTest fftwTest)