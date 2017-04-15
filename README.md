# AFQMCLAB

This is a library for AFQMC.

All rights reserved. Please do not distribute the program, or any of its parts, without explicit consent of the author.

## Dependence
   - **GoogleTest**

     set `GTEST_ROOT='/PATH/TO/GOOGLETEST'`, e.g. `export GTEST_ROOT='/home/username/lib/gtest'`

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


## How to install:
    git clone https://github.com/hshi/AFQMCLAB.git
    cd AFQMCLAB
    mkdir build
    cd build
    cmake .. -DCMAKE_INSTALL_PREFIX:PATH="~/lib/afqmclab"
    make -j4
    make test
    make install

## How to use

Frist set path to AFQMCLAB_DIR, e.g.

    export AFQMCLAB_DIR='/where/to/install/AFQMCLAB'
or

    setenv AFQMCLAB_DIR /where/to/install/AFQMCLAB

Then see tutorials for detail examples.


## Tune cmake
- Set install directory to ~/lib/afqmclab.

            cmake .. -DCMAKE_INSTALL_PREFIX:PATH="~/lib/afqmclab"

- Use magma library

            cmake .. -DUSE_MAGMA=on

- Change build type.

    - Use cmake type

            cmake .. -DCMAKE_BUILD_TYPE=Debug
            cmake .. -DCMAKE_BUILD_TYPE=Release

    - Change platform for particlular build type.

      It can be _STORM_, _HURRICANE_, _COMET_..., details are in AFQMCLAB/cmake/PLATFORM_*.cmake.

            cmake .. -DPLATFORM=platform

    - Set everything manually:

            cmake .. -DPLATFORM=MANUAL args

      - args only for MANUAL
          - Set cxx compiler: `-DCMAKE_CXX_COMPILER=mpic++`
          - (Only if we are using MPI) Set mpi executable: `-DMPIEXEC=mpiexec`
          - (Only if we are using MPI) Set mpi number of process flag: `-DMPIEXEC_NUMPROC_FLAG=-np`
          - (Only if we are using MPI) Set MPI flag: `-DUSE_MPI=on`

      - args for both MANUAL and other platform
          - Set cxx flags: ` -DCMAKE_CXX_FLAGS="-Wall -O3 -DNDEBUG" `
          - Set install path: `-DCMAKE_INSTALL_PREFIX:PATH="~/lib/afqmclab"`
          - Use magma library: `-DUSE_MAGMA=on`
          - Use 64 bit int for lapack and blas: `-DUSE_INT64=on`
          - Use openmp for lapack, blas and Lanczos code: `-DUSE_OPENMP=on`
          - ( Same with cxx flags ) Set external flags: `-DEXT_FLAGS:STRING="-Wall -O3 -DNDEBUG" `
          - ( For unusual machines ) Set external definitions: ` -DEXT_DEFINITIONS:LIST="-DSPECAIL" `
          - ( Only for system lapack, blas and ACML ) Set fortran function no underscore

                 `-DFORTRAN_NO_UNDERSCORE=on`
          - ( Only for system lapack, blas and ACML ) Set fortran function return void

                 `-DFORTRAN_COMPLEX_FUNCTIONS_RETURN_VOID=on`

      For examples, serial manual looks like:

            cmake .. -DPLATFORM=MANUAL -DCMAKE_CXX_COMPILER=icpc -DCMAKE_CXX_FLAGS="-Wall -O3 -DNDEBUG" -DUSE_OPENMP=on -DCMAKE_INSTALL_PREFIX:PATH="~/lib/afqmclab"

      MPI manual looks like:

            cmake .. -DPLATFORM=MANUAL -DCMAKE_CXX_COMPILER=mpic++ -DMPIEXEC=mpiexec -DMPIEXEC_NUMPROC_FLAG="-np" -DUSE_MPI=on -DCMAKE_CXX_FLAGS="-Wall -O3 -DNDEBUG" -DUSE_OPENMP=on -DCMAKE_INSTALL_PREFIX:PATH="~/lib/afqmclab"


## Note:

- `FFTW` wrap does not support 64 bit int and openmp.
- `MAGMA` wrap does not support 64 bit int and openmp.
- `ACML_MP` is very slow for zgetrf when OMP_NUM_THREADS=1, `MKL` is preferred for openmp jobs. 
- `ACML_MP` can be used for Lanczos code, since it does not use zgetrf.
- For intel Openmp threading, currently use flag -qopenmp (icpc) and -fopenmp (g++). While 
intel-mkl-link-line-advisor now suggests to link library -liomp5 (icpc) and -lgomp (g++). It seems okay to use flag. We 
might need to move to -openmp (icpc) later.

  //TODO: Normal simulation seems to have more infinite variance problem, check old code for benchmark. ==> Try to 
  run new code in Hurricane

  //TODO: Large simulation with trotter has large infinite variance problem, why?
  
  //TODO: Fixed infinite variance method is always lower, why?
  
  //TODO: Check normal results and fixed results v.s systems size.
  
  //TODO: Test pinning field with second order
    
  //TODO: Use inverse Force Bias to fix infinit varaince problem
  
  //TODO: Flip spin, Yuanyao mentioned is also scales as ~L?
      
  //TODO: Infinite variance?
        
  //TODO: Hurricane intel mp problem?
  
  //TODO: Think about metropolis code with sign problem. 
  
  //TODO: Write a cp code?
  
  //TODO: Write a fp code?
  
  //TODO: Try two side projection? (two side cp, two side fp)
  
  //TODO: add dynamic correlation function?
  
  //TODO: After test, add find_block in scripts.
   
  //TODO: Read and Write use HDF5 file? For exact diagonal code, it should be good.

  //TODO: FFTW GURU interface
