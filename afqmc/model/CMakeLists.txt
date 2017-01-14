add_subdirectory(HubbardRealSpaceSOC)
add_subdirectory(real_material_Hamiltonian)

add_library(afqmcModelHao STATIC
        $<TARGET_OBJECTS:afqmcHubbardRealSpaceSOCHaoObject>
        )