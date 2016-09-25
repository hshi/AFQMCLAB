#For source
set(SOURCE_HEADERS lanczos.h)
set(SOURCE_FILES lanczos.cpp)
set(SOURCE_TESTS lanczosTest.cpp)

#For library
add_library(lanczosHao OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})

#For Test
add_executable(lanczosHaoTest ${SOURCE_HEADERS}
        $<TARGET_OBJECTS:lanczosHao>
        ${SOURCE_TESTS} $<TARGET_OBJECTS:mpiHaoObject> $<TARGET_OBJECTS:tensorHaoObject>)

target_link_libraries(lanczosHaoTest libgtest-main-hao ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT}
        ${lapackblas_libraries} ${magma_cuda_libraries})

target_include_directories(lanczosHaoTest PUBLIC ${GTEST_INCLUDE_DIRS}
        ${lapackblas_include_dirs} ${magma_cuda_include_dirs})

add_my_test(lanczosHaoTest lanczosHaoTest)