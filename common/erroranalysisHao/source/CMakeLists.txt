set(SOURCE_FILES kahan.cpp serialErrorAnalysis.cpp threadErrorAnalysis.cpp)

add_library(errorAnalysisHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(errorAnalysisHao STATIC $<TARGET_OBJECTS:errorAnalysisHaoObject>)