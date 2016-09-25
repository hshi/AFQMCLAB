#For source
set(SOURCE_HEADERS realMaterialHamiltonian.h)
set(SOURCE_FILES realMaterialHamiltonian.cpp)
set(SOURCE_TESTS realMaterialHamiltonianTest.cpp)

#For library
add_library(realMaterialHamiltonianHao OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})

#For Test
add_executable(realMaterialHamiltonianHaoTest ${SOURCE_HEADERS}
        $<TARGET_OBJECTS:realMaterialHamiltonianHao>
        ${SOURCE_TESTS} $<TARGET_OBJECTS:mpiHaoObject> $<TARGET_OBJECTS:testHaoObject> $<TARGET_OBJECTS:tensorHaoObject>)

target_link_libraries(realMaterialHamiltonianHaoTest libgtest-main-hao ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT}
        ${lapackblas_libraries} ${magma_cuda_libraries})

target_include_directories(realMaterialHamiltonianHaoTest PUBLIC ${GTEST_INCLUDE_DIRS}
        ${lapackblas_include_dirs} ${magma_cuda_include_dirs})

add_my_test(realMaterialHamiltonianHaoTest realMaterialHamiltonianHaoTest)