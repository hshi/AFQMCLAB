add_executable(double_error_analysis double_error_analysis.cpp ${SOURCE_HEADERS})
target_link_libraries(double_error_analysis errorAnalysisHao mpiHao ${EXT_LIBRARIES})
install(TARGETS double_error_analysis DESTINATION bin)

add_executable(complex_double_error_analysis complex_double_error_analysis.cpp ${SOURCE_HEADERS})
target_link_libraries(complex_double_error_analysis errorAnalysisHao mpiHao ${EXT_LIBRARIES})
install(TARGETS complex_double_error_analysis DESTINATION bin)