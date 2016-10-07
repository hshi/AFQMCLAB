# AFQMCLIB

This is a library for AFQMC.

##Dependence
   - **GoogleTest**

     set `GTEST_ROOT='/PATH/TO/FFTW'`, e.g. `export GTEST_ROOT='/home/username/lib/gtest'`

   - **SPRNG** and **GMP**

     set `SPRNG='/PATH/TO/SPRNG'`, e.g. `export SPRNG='/home/username/sprng/sprng2.0'`

     set `GMP='/PATH/TO/GMP'`, e.g. `export GMP='/usr/local/gmp-4.3.2'`

   - **FFTW**

     set `FFTW='/PATH/TO/FFTW'`, e.g. `export FFTW='/opt/fftw'`

   - **LAPACK** and **BLAS**

     - MKL, set `MKL='/PATH/TO/MKL'`, e.g. `export MKL='/opt/intel/mkl'`

     - ACML, set `ACML='/PATH/TO/ACML'`, e.g. `export ACML='/usr/local/acml-5.1.0/'`

     - System LAPACK and BLAS, automatically use FindLAPACK.cmake in cmake system.

   - **MAGMA** (Optional)

     set `MAGMA='/PATH/TO/MAGMA'`, e.g. `export MAGMA='/usr/local/intel64/nehalem/magma-1.3.0'`

     Note: magma need cuda.

   - **MPI** (Optional)


##How to use:
    git clone https://github.com/hshi/AFQMCLIB.git
    cd AFQMCLIB
    mkdir build
    cd build
    cmake ..
    make
    make test


##Tune cmake
- Set install directory to ~/lib/afqmclib.

            cmake .. -DCMAKE_INSTALL_PREFIX:PATH="~/lib/afqmclib"

- Use magma library

            cmake .. -DUSE_MAGMA=on

- Change build type.

    - Use cmake type

            cmake .. -DCMAKE_BUILD_TYPE=Debug
            cmake .. -DCMAKE_BUILD_TYPE=Release

    - Change platform for particlular build type.

      It can be _STORM_, _HURRIANCE_, _COMET_..., details are in AFQMCLIB/cmake/PLATFORM_*.cmake.

            cmake .. -DPLATFORM=platform

    - Set everything manually:

            cmake .. -DPLATFORM=MANUAL args

      - args only for MANUAL
          - Set cxx compiler: `-DCMAKE_CXX_COMPILER=mpic++`
          - (Only if we are using MPI) Set mpi executable: `-DMPIEXEC=mpiexec`
          - (Only if we are using MPI) Set mpi number of process flag: `-DMPIEXEC_NUMPROC_FLAG=np`
          - (Only if we are using MPI) Set MPI flag: `-DUSE_MPI=on`

      - args for both MANUAL and other platform
          - Set cxx flags: `-DCMAKE_CXX_FLAGS="-Wall -O3 -DNDEBUG"`
          - Set install path: `-DCMAKE_INSTALL_PREFIX:PATH="~/lib/afqmclib"`
          - ( Only for system lapack, blas and ACML ), set fortran function nounderscore `-DFORTRAN_NO_UNDERSCORE=on`
          - Use magma library: `-DUSE_MAGMA=on`

      For examples, serial manual looks like:

            cmake .. -DPLATFORM=MANUAL -DCMAKE_CXX_FLAGS="-Wall -O3 -DNDEBUG" -DCMAKE_INSTALL_PREFIX:PATH="~/lib/afqmclib"

      MPI manual looks like:

            cmake .. -DPLATFORM=MANUAL -DCMAKE_CXX_COMPILER=mpic++ -DMPIEXEC=mpiexec -DMPIEXEC_NUMPROC_FLAG="-np" -DUSE_MPI=on -DCMAKE_CXX_FLAGS="-Wall -O3 -DNDEBUG" -DCMAKE_INSTALL_PREFIX:PATH="~/lib/afqmclib"

  //TODO: Check fftw with int64 and openmp ?

  //TODO: Test magma in Hurricane.

  //TODO: MAGMA int64? Update magma bin==> to fully empty!

  //TODO: MPISUM/MPIBcast only support int32? Ask question in stack?

  //TODO: FFTW64 bit?

  //TODO: Check MPI + OPENMP conflict. Learn OPENMP IN C++. ADD OPENMP IN CODE

  //TODO: Use different OPENMP FLAG? For lapackblas, fftw, all code?

  //TODO: FFTW with openmp? ==> Do we need to seperate them?

  //TODO: Lanczos: meausre dynamic correlation function exp(-b H) = 1 -b H -bb/2 *H*H. transfer particles from N to N+1,and N+1 to N

  //TODO: Use my_flags; my_libraries; my_include; my_defination for all the code.

  //TODO: How to run MPI and OPENMP Hybird job in Hurricane and storm ==> Ask Eric, and test it

  //TODO: USE_INT64 for LAPACK AND BLAS?

  //TODO: Add a resize function in Tensor_Hao, and Wf function in Lanczos.