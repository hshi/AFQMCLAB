#We can temporarily set CMAKE_CXX_FLAGS, it will not affect other directory (Checked on my local computer)
#set(CMAKE_CXX_FLAGS "-std=c++11")

set(SOURCE_HEADERS
        ${CMAKE_CURRENT_LIST_DIR}/include/kahan.h
        ${CMAKE_CURRENT_LIST_DIR}/include/serialErrorAnalysis.h
        ${CMAKE_CURRENT_LIST_DIR}/include/threadErrorAnalysis.h
        ${CMAKE_CURRENT_LIST_DIR}/include/errorAnalysis.h)

add_subdirectory(include)
add_subdirectory(source)
add_subdirectory(test)
add_subdirectory(bin)