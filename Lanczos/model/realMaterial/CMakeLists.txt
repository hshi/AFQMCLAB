#For source
set(SOURCE_HEADERS realMaterial.h)
set(SOURCE_FILES realMaterial.cpp realMaterialReadWrite.cpp)
set(SOURCE_TESTS realMaterialTest.cpp)

#For library
add_library(lanczosModelRealMaterialHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(lanczosModelRealMaterialHao STATIC $<TARGET_OBJECTS:lanczosModelRealMaterialHaoObject>)

#For Test
add_executable(lanczosModelRealMaterialTest ${SOURCE_HEADERS} ${SOURCE_TESTS} )

target_link_libraries(lanczosModelRealMaterialTest
        lanczosModelRealMaterialHao lanczosInterfaceHao libHao libgtest-main-hao ${ext_libraries})

target_include_directories(lanczosModelRealMaterialTest PUBLIC ${ext_include_dirs})

add_test(NAME lanczosModelRealMaterialTest COMMAND "$<TARGET_FILE:lanczosModelRealMaterialTest>")