add_subdirectory(hop)
add_subdirectory(hop2s)
add_subdirectory(hop2is)
add_subdirectory(logHop2is)

file(RELATIVE_PATH relativeDirectorPath ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_LIST_DIR})
install(FILES oneBodyOperator.h DESTINATION "include/${relativeDirectorPath}")
