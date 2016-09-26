#Base level, can be used for everything
add_subdirectory(test_hao)
add_subdirectory(mpi_hao)
add_subdirectory(time_hao)

#First level
add_subdirectory(error_analysis)
add_subdirectory(random_number)
add_subdirectory(tensor_hao)
add_subdirectory(fftw_hao)
add_subdirectory(math_hao)

add_library(libHao STATIC
        $<TARGET_OBJECTS:testHaoObject>
        $<TARGET_OBJECTS:mpiHaoObject>
        $<TARGET_OBJECTS:timeHaoObject>
        $<TARGET_OBJECTS:errorAnalysisHaoObject>
        $<TARGET_OBJECTS:randomNumberHaoObject>
        $<TARGET_OBJECTS:tensorHaoObject>
        $<TARGET_OBJECTS:fftwHaoObject>
        $<TARGET_OBJECTS:mathHaoObject>
        )