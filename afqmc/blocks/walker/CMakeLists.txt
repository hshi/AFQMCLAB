add_subdirectory(SD)

file(RELATIVE_PATH relativeDirectorPath ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_LIST_DIR})
install(FILES walker.h DESTINATION "include/${relativeDirectorPath}")