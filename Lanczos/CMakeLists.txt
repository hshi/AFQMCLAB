add_subdirectory(interface)
add_subdirectory(model)

add_library(lanczos STATIC
        $<TARGET_OBJECTS:lanczosInterfaceHaoObject>
        $<TARGET_OBJECTS:lanczosModelFullMatrixHaoObject>
        $<TARGET_OBJECTS:lanczosModelSparseMatrixHaoObject>
        $<TARGET_OBJECTS:lanczosBasisHaoObject>
        $<TARGET_OBJECTS:lanczosModelRealMaterialHaoObject>
        )
install(TARGETS lanczos DESTINATION lib EXPORT lanczosTargets)
install(EXPORT lanczosTargets DESTINATION cmake)

file(RELATIVE_PATH relativeDirectorPath ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_LIST_DIR})
install(FILES lanczos.h DESTINATION "include/${relativeDirectorPath}")