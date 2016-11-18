set(SOURCE_HEADERS
        ${CMAKE_CURRENT_LIST_DIR}/include/random_hao.h)

add_definitions(${sprng_definitions})
include_directories(${sprng_include_dirs})

add_subdirectory(include)
add_subdirectory(source)
add_subdirectory(test)