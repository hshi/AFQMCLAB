#Base level, can be used for everything
add_subdirectory(testHao)
add_subdirectory(mpiHao)
add_subdirectory(timeHao)

#First level
add_subdirectory(erroranalysisHao)
add_subdirectory(randomHao)
add_subdirectory(tensorHao)
add_subdirectory(fftwHao)
add_subdirectory(mathHao)
add_subdirectory(lapackblasHao)

#Second level
add_subdirectory(readWriteHao)

add_library(libHao STATIC
        $<TARGET_OBJECTS:testHaoObject>
        $<TARGET_OBJECTS:mpiHaoObject>
        $<TARGET_OBJECTS:timeHaoObject>
        $<TARGET_OBJECTS:errorAnalysisHaoObject>
        $<TARGET_OBJECTS:randomNumberHaoObject>
        $<TARGET_OBJECTS:tensorHaoObject>
        $<TARGET_OBJECTS:fftwHaoObject>
        $<TARGET_OBJECTS:mathHaoObject>
        $<TARGET_OBJECTS:readWriteHaoObject>
        )
install(TARGETS libHao DESTINATION lib EXPORT libHaoTargets)
install(EXPORT libHaoTargets DESTINATION cmake)

file(RELATIVE_PATH relativeDirectorPath ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_LIST_DIR})
install(FILES libhao.h DESTINATION "include/${relativeDirectorPath}")