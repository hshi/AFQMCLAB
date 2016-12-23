set(SOURCE_TESTS sparseMatrixTest.cpp)

add_executable(lanczosModelSparseMatrixTest ${SOURCE_HEADERS} ${SOURCE_TESTS} )

target_link_libraries(lanczosModelSparseMatrixTest
        lanczosModelSparseMatrixHao lanczosInterfaceHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_test(NAME lanczosModelSparseMatrixTest COMMAND "$<TARGET_FILE:lanczosModelSparseMatrixTest>")