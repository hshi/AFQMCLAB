add_subdirectory(HubbardRealSpaceSOC)
add_subdirectory(realMaterialMolecule)
#add_subdirectory(real_material_Hamiltonian)

add_library(afqmcModelHao STATIC
        $<TARGET_OBJECTS:afqmcHubbardRealSpaceSOCHaoObject>
        $<TARGET_OBJECTS:afqmcRealMaterialMoleculeHaoObject>
        )

file(RELATIVE_PATH relativeDirectorPath ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_LIST_DIR})
install(FILES model.h DESTINATION "include/${relativeDirectorPath}")