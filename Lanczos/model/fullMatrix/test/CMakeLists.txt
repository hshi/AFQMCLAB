set(SOURCE_TESTS fullMatrixTest.cpp)

add_executable(lanczosModelFullMatrixTest ${SOURCE_HEADERS} ${SOURCE_TESTS} )

target_link_libraries(lanczosModelFullMatrixTest
        lanczosModelFullMatrixHao lanczosInterfaceHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_test( NAME lanczosModelFullMatrixTest COMMAND "$<TARGET_FILE:lanczosModelFullMatrixTest>")