add_subdirectory(NiupNidnSDOperation)

file(RELATIVE_PATH relativeDirectorPath ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_LIST_DIR})
install(FILES twoBodyWalkerOperation.h DESTINATION "include/${relativeDirectorPath}")