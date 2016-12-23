set(SOURCE_TESTS SpinlessFermionsTest.cpp)

add_executable(lanczosModelSpinlessFermionsTest ${SOURCE_HEADERS} ${SOURCE_TESTS} )

target_link_libraries(lanczosModelSpinlessFermionsTest
        lanczosModelSpinlessFermionsHao lanczosBasisHao lanczosInterfaceHao libHao gtest_main_hao ${EXT_LIBRARIES})

add_test(NAME lanczosModelSpinlessFermionsTest COMMAND "$<TARGET_FILE:lanczosModelSpinlessFermionsTest>")