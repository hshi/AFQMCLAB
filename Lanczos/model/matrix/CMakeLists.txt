#For source
set(SOURCE_HEADERS fullMatrix.h)
set(SOURCE_FILES fullMatrix.cpp)
set(SOURCE_TESTS fullMatrixTest.cpp)

#For library
add_library(lanczosModelFullMatrixHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(lanczosModelFullMatrixHao STATIC $<TARGET_OBJECTS:lanczosModelFullMatrixHaoObject>)

#For Test
add_executable(lanczosModelFullMatrixTest ${SOURCE_HEADERS} ${SOURCE_TESTS} )

target_link_libraries(lanczosModelFullMatrixTest
        lanczosModelFullMatrixHao lanczosInterfaceHao libHao libgtest-main-hao ${ext_libraries})

target_include_directories(lanczosModelFullMatrixTest PUBLIC ${ext_include_dirs})

add_test( NAME lanczosModelFullMatrixTest COMMAND "$<TARGET_FILE:lanczosModelFullMatrixTest>")