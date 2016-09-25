# AFQMCLIB

This is a library for AFQMC.

##Dependence
   - **GoogleTest**

     set `GTEST_ROOT='/PATH/TO/FFTW'`, e.g. `export GTEST_ROOT='/home/boruoshihao/lib/gtest'`

   - **FFTW**

     set `FFTW='/PATH/TO/FFTW'`, e.g. `export FFTW='/opt/fftw'`

   - **LAPACK** and **BLAS**

     - MKL, set `MKL='/PATH/TO/MKL'`, e.g. `export MKL='/opt/intel/mkl'`

     - ACML, set `ACML='/PATH/TO/ACML'`, e.g. `export ACML='/usr/local/acml-5.1.0/'`

     - System LAPACK and BLAS, automatically use FindLAPACK.cmake in cmake system.

   - **SPRNG** and **GMP**

     set `SPRNG='/PATH/TO/SPRNG'`, e.g. `export SPRNG='/home/username/sprng/sprng2.0'`

     set `GMP='/PATH/TO/GMP'`, e.g. `export GMP='/usr/local/gmp-4.3.2'`


   - **MPI** (Optional)

   - **MAGMA** (Optional)

     set `MAGMA='/PATH/TO/MAGMA'`, e.g. `export MAGMA='/usr/local/intel64/nehalem/magma-1.3.0'`

     Note: magma need cuda.

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

- Use magma library

            cmake .. -DUSE_MAGMA=on -DCMAKE_INSTALL_PREFIX:PATH="~/lib/afqmclib"

- If defualt setting does not work, change to different platform.

  It can be _STORM_, _HURRIANCE_, _COMET_..., details are in AFQMCLIB/cmake/PLATFORM_*.cmake.

            cmake .. -DPLATFORM=platform -DCMAKE_INSTALL_PREFIX:PATH="~/lib/afqmclib"

- If nothing works for these platforms, set everything manually:

            cmake .. -DPLATFORM=MANUAL args

  - args only for MANUAL
      - Set cxx compiler: `-DCMAKE_CXX_COMPILER=mpic++`
      - (Only if we are using MPI) Set mpi executable: `-DMPIEXEC=mpiexec`
      - (Only if we are using MPI) Set mpi number of process flag: `-DMPIEXEC_NUMPROC_FLAG=np`
      - (Only if we are using MPI) Set MPI flag: `-DUSE_MPI=on`

  - args for both MANUAL and other platform
      - Set cxx flags: `-DCMAKE_CXX_FLAGS="-Wall -O3"`
      - Set install path: `-DCMAKE_INSTALL_PREFIX:PATH="~/lib/afqmclib"`
      - ( Only for system lapack, blas and ACML ), set fortran function nounderscore `-DFORTRAN_NO_UNDERSCORE=on`
      - Use magma library: `-DUSE_MAGMA=on`

  For examples, serial manual looks like:

            cmake .. -DPLATFORM=MANUAL -DCMAKE_CXX_FLAGS="-Wall -O3" -DCMAKE_INSTALL_PREFIX:PATH="~/lib/afqmclib"

  MPI manual looks like:

            cmake .. -DPLATFORM=MANUAL -DCMAKE_CXX_COMPILER=mpic++ -DMPIEXEC=mpiexec -DMPIEXEC_NUMPROC_FLAG="-np" -DUSE_MPI=on -DCMAKE_CXX_FLAGS="-Wall -O3" -DCMAKE_INSTALL_PREFIX:PATH="~/lib/afqmclib"

  //TODO: Test magma in Hurricane.

  //TODO: ALL LIBALL, COMBINE ALL BASE LIBRARY TOGETHER

  //TODO: ADD OPENMP IN CODE

  //TODO: Add debug flag