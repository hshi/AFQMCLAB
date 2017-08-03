set(SOURCE_HEADERS
        ${CMAKE_CURRENT_LIST_DIR}/include/HubbardSOC.h
        ${CMAKE_CURRENT_LIST_DIR}/include/HubbardSOCAll.h
        ${CMAKE_CURRENT_LIST_DIR}/include/HubbardSOCMeasureCommuteSDSD.h
        ${CMAKE_CURRENT_LIST_DIR}/include/HubbardSOCMeasureFixedSDSD.h
        ${CMAKE_CURRENT_LIST_DIR}/include/HubbardSOCMeasureObserveSDSD.h
        ${CMAKE_CURRENT_LIST_DIR}/include/HubbardSOCSDOperation.h
        )

add_subdirectory(include)
add_subdirectory(source)
add_subdirectory(test)
add_subdirectory(bin)