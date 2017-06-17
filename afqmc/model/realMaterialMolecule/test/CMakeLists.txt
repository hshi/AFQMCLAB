set(SOURCE_TESTS
        realMaterialMoleculeTest.cpp
        realMaterialMoleculeFixedSD2sSD2isTest.cpp)

add_executable(afqmcRealMaterialMoleculeTest ${SOURCE_HEADERS} ${SOURCE_TESTS})

target_link_libraries(afqmcRealMaterialMoleculeTest afqmcRealMaterialMoleculeHao afqmcUtilitiesHao afqmcBlocksHao
        commonHao gtest_mainHao ${EXT_LIBRARIES})

add_my_test(afqmcRealMaterialMoleculeTest "$<TARGET_FILE:afqmcRealMaterialMoleculeTest>")