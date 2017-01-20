set(SOURCE_FILES
        afqmcMetropolis.cpp
        afqmcMetropolisMeasure.cpp
        afqmcMetropolisSetWalkerAndField.cpp
        afqmcMetropolisMethod.cpp
        afqmcMetropolisUpdate.cpp
        main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_HEADERS} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${AFQMCLAB_LIBRARIES})