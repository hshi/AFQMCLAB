import sys
import os
sys.path.append( os.environ['AFQMCLAB_DIR']+"/scripts/supercubic" )
from lattClass import *

if len(sys.argv) < 2:
    sys.exit("Missing arguments!!! Example: python initialOrderParameter.py zafm")
typ = sys.argv[1]

latt  = Latt_class.read("latt_param")
f =  open("model_param", 'r')
L3 = int( f.readline() )
N =  int( f.readline() )
f.close()

if L3 != 3*latt.L :
    sys.exit("Lattice size is not consistent in latt_param and model_param!")

n_mean = float(N)/L3

density = np.zeros(2*L3, dtype=complex)
spinOrbit = np.zeros(2*L3, dtype=complex)
if typ=="zafm":
    for i in range(latt.L):
        coor=np.array(latt.coor(i))
        if coor.sum()%2==0:
            density[i]    = n_mean
        else:
            density[i+L3] = n_mean
elif typ=="xafm":
    for i in range(latt.L):
        coor=np.array(latt.coor(i))
        if coor.sum()%2==0:
            spinOrbit[i]    = n_mean/2.0
            spinOrbit[i+L3] = n_mean/2.0
        else:
            spinOrbit[i]    = -n_mean/2.0
            spinOrbit[i+L3] = -n_mean/2.0
elif typ=="yafm":
    for i in range(latt.L):
        coor=np.array(latt.coor(i))
        if coor.sum()%2==0:
            spinOrbit[i]    =  1j*n_mean/2.0
            spinOrbit[i+L3] = -1j*n_mean/2.0
        else:
            spinOrbit[i]    = -1j*n_mean/2.0
            spinOrbit[i+L3] =  1j*n_mean/2.0
elif typ=="random":
    for i in range(L3):
        density[i]      = np.random.random()
        density[i+L3]   = np.random.random()
        spinOrbit[i]    = np.random.random() + 1j*np.random.random()
        spinOrbit[i+L3] = np.conj( spinOrbit[i] )


np.savetxt("density.dat", np.column_stack(( np.real(density), np.imag(density) )),fmt=('%26.16e', '%26.16e'),
           header="{:26d} \n{:26d}".format(1, L3*2), comments='')
np.savetxt("spinOrbit.dat", np.column_stack(( np.real(spinOrbit), np.imag(spinOrbit) )),fmt=('%26.16e', '%26.16e'),
           header="{:26d} \n{:26d}".format(1, L3*2), comments='')
