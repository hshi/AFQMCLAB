add_executable(doubleErrorAnalysis doubleErrorAnalysis.cpp ${SOURCE_HEADERS})
target_link_libraries(doubleErrorAnalysis errorAnalysisHao mpiHao ${EXT_LIBRARIES})
install(TARGETS doubleErrorAnalysis DESTINATION bin)

add_executable(complexDoubleErrorAnalysis complexDoubleErrorAnalysis.cpp ${SOURCE_HEADERS})
target_link_libraries(complexDoubleErrorAnalysis errorAnalysisHao mpiHao ${EXT_LIBRARIES})
install(TARGETS complexDoubleErrorAnalysis DESTINATION bin)