set(SOURCE_TESTS Hmatrix.h Hmatrix.cpp LanczosTest.cpp LanczosBasisWfTest.cpp measureBasedOnLanMatrixTest.cpp)

add_executable(lanczosInterfaceTest ${SOURCE_HEADERS} ${SOURCE_TESTS} )

target_link_libraries(lanczosInterfaceTest lanczosInterfaceHao commonHao gtest_mainHao ${EXT_LIBRARIES})

add_test( NAME lanczosInterfaceTest COMMAND "$<TARGET_FILE:lanczosInterfaceTest>")