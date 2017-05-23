add_subdirectory(SDSDOperation)
add_subdirectory(SD2sSD2isOperation)

file(RELATIVE_PATH relativeDirectorPath ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_LIST_DIR})
install(FILES walkerWalkerOperation.h DESTINATION "include/${relativeDirectorPath}")