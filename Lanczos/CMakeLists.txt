add_subdirectory(interface)
add_subdirectory(model)

add_library(lanczosHao STATIC
        $<TARGET_OBJECTS:lanczosInterfaceHaoObject>
        $<TARGET_OBJECTS:lanczosModelFullMatrixHaoObject>
        $<TARGET_OBJECTS:lanczosModelSparseMatrixHaoObject>
        $<TARGET_OBJECTS:lanczosBasisHaoObject>
        $<TARGET_OBJECTS:lanczosModelRealMaterialHaoObject>
        $<TARGET_OBJECTS:lanczosModelSpinlessFermionsHaoObject>
        )
install(TARGETS lanczosHao DESTINATION lib EXPORT lanczosHaoTargets)
install(EXPORT lanczosHaoTargets DESTINATION cmake)

file(RELATIVE_PATH relativeDirectorPath ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_LIST_DIR})
install(FILES lanczos.h DESTINATION "include/${relativeDirectorPath}")