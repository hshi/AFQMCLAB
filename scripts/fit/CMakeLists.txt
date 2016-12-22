set(SOURCE_SCRIPTS fit.py fit_linear.py fit_linear_yerr.py)

file(RELATIVE_PATH relativeDirectorPath ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_LIST_DIR})
install(FILES ${SOURCE_SCRIPTS} DESTINATION "${relativeDirectorPath}")