#For source
set(SOURCE_HEADERS include/fftw_define.h include/fftw_hao.h)

set(SOURCE_FILES source/fftw_hao.cpp)

set(SOURCE_TESTS test/fftw_hao_test.cpp)

#For library
add_library(fftwhao OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
target_include_directories(fftwhao PUBLIC ${fftw_include_dirs})

#For Test
add_executable(fftwhaotest ${SOURCE_HEADERS} $<TARGET_OBJECTS:fftwhao>
        ${SOURCE_TESTS} $<TARGET_OBJECTS:mpihao>)

target_link_libraries(fftwhaotest libgtest-main-hao ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT}
        ${fftw_libraries})

target_include_directories(fftwhaotest PUBLIC ${GTEST_INCLUDE_DIRS} ${fftw_include_dirs})

add_my_test(fftwhaotest fftwhaotest)