#For source
set(SOURCE_HEADERS realMaterialHamiltonian.h)
set(SOURCE_FILES realMaterialHamiltonian.cpp)
set(SOURCE_TESTS realMaterialHamiltonianTest.cpp)

#For library
add_library(realMaterialHamiltonianHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(realMaterialHamiltonianHao STATIC $<TARGET_OBJECTS:realMaterialHamiltonianHaoObject>)

#For Test
add_executable(realMaterialHamiltonianTest ${SOURCE_HEADERS} ${SOURCE_TESTS})

target_link_libraries(realMaterialHamiltonianTest realMaterialHamiltonianHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(realMaterialHamiltonianTest "$<TARGET_FILE:realMaterialHamiltonianTest>")