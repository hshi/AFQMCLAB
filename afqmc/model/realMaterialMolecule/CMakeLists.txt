set(SOURCE_HEADERS
        ${CMAKE_CURRENT_LIST_DIR}/include/realMaterialMolecule.h
        ${CMAKE_CURRENT_LIST_DIR}/include/realMaterialMoleculeMeasureFixedSD2sSD2is.h
        ${CMAKE_CURRENT_LIST_DIR}/include/realMaterialMoleculeSD2isOperation.h
        ${CMAKE_CURRENT_LIST_DIR}/include/realMaterialMoleculeSD2sOperation.h
        ${CMAKE_CURRENT_LIST_DIR}/include/realMaterialMoleculeAll.h
        )

add_subdirectory(include)
add_subdirectory(source)
add_subdirectory(test)