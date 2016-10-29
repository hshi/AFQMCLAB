#For source
set(SOURCE_HEADERS lanczosBasis.h)
set(SOURCE_FILES lanczosBasis.cpp)
set(SOURCE_TESTS lanczosBasisTest.cpp)

#For library
add_library(lanczosBasisHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(lanczosBasisHao STATIC $<TARGET_OBJECTS:lanczosBasisHaoObject>)

#For Test
add_executable(lanczosBasisTest ${SOURCE_HEADERS} ${SOURCE_TESTS})

target_link_libraries(lanczosBasisTest lanczosBasisHao libHao libgtest-main-hao ${ext_libraries})

target_include_directories(lanczosBasisTest PUBLIC ${ext_include_dirs})

add_test( NAME lanczosBasisTest COMMAND "$<TARGET_FILE:lanczosBasisTest>")