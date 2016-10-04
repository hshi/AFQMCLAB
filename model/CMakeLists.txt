add_definitions(${ext_definitions})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ext_flags}")
removeDuplicateSubstring(${CMAKE_CXX_FLAGS} CMAKE_CXX_FLAGS)

add_subdirectory(real_material_Hamiltonian)