add_subdirectory(hopSDOperation)
add_subdirectory(hop2sSD2sOperation)
add_subdirectory(hop2isSD2isOperation)
add_subdirectory(logHop2isSD2isOperation)

file(RELATIVE_PATH relativeDirectorPath ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_LIST_DIR})
install(FILES oneBodyWalkerOperation.h DESTINATION "include/${relativeDirectorPath}")
