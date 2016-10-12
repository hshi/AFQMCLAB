#For source
set(SOURCE_HEADERS
        include/Lanczos.h
        include/LanczosBasisWf.h)
set(SOURCE_FILES
        source/Lanczos.cpp
        source/LanczosBasisWf.cpp)
set(SOURCE_TESTS
        test/LanczosTest.cpp
        test/LanczosBasisWfTest.cpp)

#For library
add_library(lanczosHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(lanczosHao STATIC $<TARGET_OBJECTS:lanczosHaoObject>)

#For Test
add_executable(lanczosTest ${SOURCE_HEADERS} ${SOURCE_TESTS} )

target_link_libraries(lanczosTest lanczosHao libHao ${ext_libraries} libgtest-main-hao)

target_include_directories(lanczosTest PUBLIC ${ext_include_dirs})

add_my_test(lanczosTest "$<TARGET_FILE:lanczosTest>")
