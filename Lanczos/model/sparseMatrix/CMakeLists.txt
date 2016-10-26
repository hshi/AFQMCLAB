#For source
set(SOURCE_HEADERS sparseMatrix.h)
set(SOURCE_FILES sparseMatrix.cpp)
set(SOURCE_TESTS sparseMatrixTest.cpp)

#For library
add_library(lanczosModelSparseMatrixHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(lanczosModelSparseMatrixHao STATIC $<TARGET_OBJECTS:lanczosModelSparseMatrixHaoObject>)

#For Test
add_executable(lanczosModelSparseMatrixTest ${SOURCE_HEADERS} ${SOURCE_TESTS} )

target_link_libraries(lanczosModelSparseMatrixTest
        lanczosModelSparseMatrixHao lanczosInterfaceHao libHao libgtest-main-hao ${ext_libraries})

target_include_directories(lanczosModelSparseMatrixTest PUBLIC ${ext_include_dirs})

add_test(NAME lanczosModelSparseMatrixTest COMMAND "$<TARGET_FILE:lanczosModelSparseMatrixTest>")