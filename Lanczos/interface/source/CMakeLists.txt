set(SOURCE_FILES
        LanczosInterface.cpp
        LanczosReadAndWrite.cpp
        LanczosUtilities.cpp
        LanczosGenerateMatrix.cpp
        LanczosBasisWf.cpp
        LanczosParam.cpp
        measureBasedOnLanMatrix.cpp)

add_library(lanczosInterfaceHaoObject OBJECT ${SOURCE_HEADERS} ${SOURCE_FILES})
add_library(lanczosInterfaceHao STATIC $<TARGET_OBJECTS:lanczosInterfaceHaoObject>)