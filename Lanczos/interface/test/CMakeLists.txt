set(SOURCE_TESTS LanczosTest.cpp LanczosBasisWfTest.cpp)

add_executable(lanczosInterfaceTest ${SOURCE_HEADERS} ${SOURCE_TESTS} )

target_link_libraries(lanczosInterfaceTest lanczosInterfaceHao libHao libgtest-main-hao ${EXT_LIBRARIES})

add_test( NAME lanczosInterfaceTest COMMAND "$<TARGET_FILE:lanczosInterfaceTest>")