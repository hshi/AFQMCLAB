add_subdirectory(hop)
add_subdirectory(hop2S)
add_subdirectory(hop2IS)
add_subdirectory(logHop2IS)

file(RELATIVE_PATH relativeDirectorPath ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_LIST_DIR})
install(FILES oneBodyOperator.h DESTINATION "include/${relativeDirectorPath}")
