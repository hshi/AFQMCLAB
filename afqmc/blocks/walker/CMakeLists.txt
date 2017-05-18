add_subdirectory(SD)
add_subdirectory(SD2S)

file(RELATIVE_PATH relativeDirectorPath ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_LIST_DIR})
install(FILES walker.h DESTINATION "include/${relativeDirectorPath}")
