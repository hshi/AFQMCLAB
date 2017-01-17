add_subdirectory(hopSDOperation)

file(RELATIVE_PATH relativeDirectorPath ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_LIST_DIR})
install(FILES oneBodyWalkerOperation.h DESTINATION "include/${relativeDirectorPath}")