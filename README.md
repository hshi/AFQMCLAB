# AFQMCLIB

This is a library for AFQMC.


##How to use:
    git clone https://github.com/hshi/AFQMCLIB.git
    cd AFQMCLIB
    mkdir build
    cd build
    cmake ..
    make
    make test
    make install


##Tune cmake
- Set install directory to ~/lib/afqmclib.

            cmake .. -DCMAKE_INSTALL_PREFIX:PATH="~/lib/afqmclib"

- If defualt setting not working, change to different platform.

  It can be _STORM_, _HURRIANCE_, _COMET_..., details are in AFQMCLIB/cmake/PLATFORM_*.cmake.

            cmake .. -DPLATFORM=platform

- If nothing works for these platforms, set everything manually:

            cmake .. -DPLATFORM=MANUAL

this is a test

`<addr>`