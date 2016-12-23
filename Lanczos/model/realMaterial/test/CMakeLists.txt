set(SOURCE_TESTS realMaterialTest.cpp)

add_executable(lanczosModelRealMaterialTest ${SOURCE_HEADERS} ${SOURCE_TESTS} )

target_link_libraries(lanczosModelRealMaterialTest
        lanczosModelRealMaterialHao lanczosBasisHao lanczosInterfaceHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_test(NAME lanczosModelRealMaterialTest COMMAND "$<TARGET_FILE:lanczosModelRealMaterialTest>")