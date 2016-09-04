# AFQMCLIB

This is a library for AFQMC.

##Dependence

This code depends on fftw, ...

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

            cmake .. -DPLATFORM=platform -DCMAKE_INSTALL_PREFIX:PATH="~/lib/afqmclib"

- If nothing works for these platforms, set everything manually:

            cmake .. -DPLATFORM=MANUAL args

  args can be

  - Set cxx compiler: `-DCMAKE_CXX_COMPILER=mpic++`
  - (Only if we are using MPI) Set mpi executable: `-DMPIEXEC=mpiexec`
  - (Only if we are using MPI) Set mpi number of process flag: `-DMPIEXEC_NUMPROC_FLAG=np`
  - (Only if we are using MPI) Set MPI flag: `-DCOMPILER_EXTRA_DEF:STRING="-DMPI_HAO"`
  - Set cxx flags: `-DCMAKE_CXX_FLAGS="-Wall -O3"`
  - Set install path: `-DCMAKE_INSTALL_PREFIX:PATH="~/lib/afqmclib"`

  For examples, serial manual looks like:

            cmake .. -DPLATFORM=MANUAL -DCMAKE_CXX_FLAGS="-Wall -O3" -DCMAKE_INSTALL_PREFIX:PATH="~/lib/afqmclib"

  MPI manual looks like:

            cmake .. -DPLATFORM=MANUAL -DCMAKE_CXX_COMPILER=mpic++ -DMPIEXEC=mpiexec -DDMPIEXEC_NUMPROC_FLAG="-np" -DCOMPILER_EXTRA_DEF:STRING="-DMPI_HAO" -DCMAKE_CXX_FLAGS="-Wall -O3" -DCMAKE_INSTALL_PREFIX:PATH="~/lib/afqmclib"