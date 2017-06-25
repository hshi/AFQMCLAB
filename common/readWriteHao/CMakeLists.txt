set(SOURCE_HEADERS
        ${CMAKE_CURRENT_LIST_DIR}/include/readWriteFstream.h
        ${CMAKE_CURRENT_LIST_DIR}/include/readWriteStringFile.h
        ${CMAKE_CURRENT_LIST_DIR}/include/readWriteHdf5.h
        ${CMAKE_CURRENT_LIST_DIR}/include/readWriteHao.h
        ${CMAKE_CURRENT_LIST_DIR}/include/readBySearchString.h)

add_subdirectory(include)
add_subdirectory(source)
add_subdirectory(test)