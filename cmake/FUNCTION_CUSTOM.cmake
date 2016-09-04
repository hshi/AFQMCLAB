#For add test, mpi or serial
function(add_my_test name executable)
    if (MPIEXEC)
        add_test( NAME ${name} COMMAND ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} 4 ${executable} )
    else()
        add_test( NAME ${name} COMMAND ${executable} )
    endif ()
endfunction(add_my_test)