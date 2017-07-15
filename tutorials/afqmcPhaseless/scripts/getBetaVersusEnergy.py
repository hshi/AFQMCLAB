import numpy as np
import subprocess
import os

beta               = np.loadtxt( "beta.dat",  unpack=True )
HNumReal, HNumImag = np.loadtxt( "HNum.dat",  unpack=True )
DenReal, DenImag   = np.loadtxt( "den.dat",   unpack=True )

E = ( HNumReal+1j*HNumImag ) / ( DenReal+1j*DenImag )
EReal = np.real(E)
EImag = np.imag(E)

np.savetxt("energyVersusBeta.dat", np.column_stack( (beta,EReal,EImag) ), fmt=('%26.16e','%26.16e','%26.16e') )
np.savetxt("energySimple.dat", np.column_stack( (EReal,) ), fmt=('%26.16e',) )