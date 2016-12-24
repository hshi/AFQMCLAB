#For source
set(SOURCE_HEADERS
        ${CMAKE_CURRENT_LIST_DIR}/include/LanczosInterface.h
        ${CMAKE_CURRENT_LIST_DIR}/include/LanczosBasisWf.h
        ${CMAKE_CURRENT_LIST_DIR}/include/LanczosExcepts.h
        ${CMAKE_CURRENT_LIST_DIR}/include/LanczosParam.h
        ${CMAKE_CURRENT_LIST_DIR}/include/modelInterface.h
        ${CMAKE_CURRENT_LIST_DIR}/include/measureBasedOnLanMatrix.h
        ${CMAKE_CURRENT_LIST_DIR}/include/LanczosInterfaceAll.h)

add_subdirectory(include)
add_subdirectory(source)
add_subdirectory(test)