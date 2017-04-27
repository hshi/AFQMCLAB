import numpy as np

beta               = np.loadtxt( "beta.dat", usecols=(0,),  unpack=True )
HNumReal, HNumImag = np.loadtxt( "HNum.dat", usecols=(0,1), unpack=True )
DenReal, DenImag   = np.loadtxt( "den.dat",  usecols=(0,1), unpack=True )

E = ( HNumReal+1j*HNumImag ) / ( DenReal+1j*DenImag )
EReal = np.real(E)
EImag = np.imag(E)
np.savetxt("energyVersusBeta.dat", np.column_stack( (beta,EReal,EImag) ), fmt=('%26.16e','%26.16e','%26.16e') )