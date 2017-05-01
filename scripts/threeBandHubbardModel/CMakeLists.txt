set(SOURCE_SCRIPTS threeBandHubbardModelHopping.py)

file(RELATIVE_PATH relativeDirectorPath ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_LIST_DIR})
install(FILES ${SOURCE_SCRIPTS} DESTINATION "${relativeDirectorPath}")