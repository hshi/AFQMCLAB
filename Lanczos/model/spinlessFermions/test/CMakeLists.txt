set(SOURCE_TESTS SpinlessFermionsTest.cpp)

add_executable(lanczosModelSpinlessFermionsTest ${SOURCE_HEADERS} ${SOURCE_TESTS} )

target_link_libraries(lanczosModelSpinlessFermionsTest
        lanczosModelSpinlessFermionsHao lanczosBasisHao lanczosInterfaceHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_test(NAME lanczosModelSpinlessFermionsTest COMMAND "$<TARGET_FILE:lanczosModelSpinlessFermionsTest>")