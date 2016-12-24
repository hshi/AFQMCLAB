set(SOURCE_FILES sparseMatrix.cpp)

add_library(lanczosModelSparseMatrixHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})

add_library(lanczosModelSparseMatrixHao STATIC $<TARGET_OBJECTS:lanczosModelSparseMatrixHaoObject>)