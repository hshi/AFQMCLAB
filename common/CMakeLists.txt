#Base level, can be used for everything
add_subdirectory(testHao)
add_subdirectory(mpiHao)
add_subdirectory(timeHao)
add_subdirectory(hdf5Hao)

#First level
add_subdirectory(erroranalysisHao)
add_subdirectory(randomHao)
add_subdirectory(tensorHao)
add_subdirectory(fftwHao)
add_subdirectory(mathHao)
add_subdirectory(lapackblasHao)
add_subdirectory(readWriteHao)

#Second level
add_subdirectory(latticeHao)

add_library(commonHao STATIC
        $<TARGET_OBJECTS:testHaoObject>
        $<TARGET_OBJECTS:mpiHaoObject>
        $<TARGET_OBJECTS:timeHaoObject>
        $<TARGET_OBJECTS:hdf5CustomHaoObject>
        $<TARGET_OBJECTS:errorAnalysisHaoObject>
        $<TARGET_OBJECTS:randomNumberHaoObject>
        $<TARGET_OBJECTS:tensorHaoObject>
        $<TARGET_OBJECTS:fftwHaoObject>
        $<TARGET_OBJECTS:mathHaoObject>
        $<TARGET_OBJECTS:readWriteHaoObject>
        $<TARGET_OBJECTS:latticeHaoObject>
        )
install(TARGETS commonHao DESTINATION lib EXPORT commonHaoTargets)
install(EXPORT commonHaoTargets DESTINATION cmake)

file(RELATIVE_PATH relativeDirectorPath ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_LIST_DIR})
install(FILES common.h DESTINATION "include/${relativeDirectorPath}")