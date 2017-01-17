add_subdirectory(NiNj)
add_subdirectory(NiupNidn)

file(RELATIVE_PATH relativeDirectorPath ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_LIST_DIR})
install(FILES twoBodyOperator.h DESTINATION "include/${relativeDirectorPath}")