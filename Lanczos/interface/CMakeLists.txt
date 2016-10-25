#For source
set(SOURCE_HEADERS
        include/Lanczos.h
        include/LanczosBasisWf.h
        include/LanczosExcepts.h
        include/LanczosParam.h
        include/modelInterface.h)
set(SOURCE_FILES
        source/Lanczos.cpp
        source/LanczosReadAndWrite.cpp
        source/LanczosUtilities.cpp
        source/LanczosGenerateMatrix.cpp
        source/LanczosBasisWf.cpp
        source/LanczosParam.cpp)
set(SOURCE_TESTS
        test/LanczosTest.cpp
        test/LanczosBasisWfTest.cpp)

#For library
add_library(lanczosInterfaceHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(lanczosInterfaceHao STATIC $<TARGET_OBJECTS:lanczosInterfaceHaoObject>)

#For Test
add_executable(lanczosInterfaceTest ${SOURCE_HEADERS} ${SOURCE_TESTS} )

target_link_libraries(lanczosInterfaceTest lanczosInterfaceHao libHao libgtest-main-hao ${ext_libraries})

target_include_directories(lanczosInterfaceTest PUBLIC ${ext_include_dirs})

add_test( NAME lanczosInterfaceTest COMMAND "$<TARGET_FILE:lanczosInterfaceTest>")