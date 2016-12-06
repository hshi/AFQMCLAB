set(SOURCE_SCRIPTS lattClass.py setDispersion.py setHoping.py)

file(RELATIVE_PATH relativeDirectorPath ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_LIST_DIR})
install(FILES ${SOURCE_SCRIPTS} DESTINATION "${relativeDirectorPath}")