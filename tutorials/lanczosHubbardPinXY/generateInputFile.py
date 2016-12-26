import sys
import os
sys.path.append( os.environ['AFQMCLAB_DIR']+"/scripts/supercubic" )
from setHoping import *

latt_n   = [2,4]
ktwist   = [0.0,0.0]
t1       = 1.0
U        = 4.0
mu       = 2.0
hz       = 2.49652
hpin     = 1.0
Ntot     = 8

#Set lattice information
latt = Latt_class( latt_n )
latt_i, latt_j, latt_hopping = HubbardNearestNeighborHopping(latt, ktwist, t1)

#Set Hopping K
pin_i     = [ 0,         latt.L,    1,        1+latt.L ]
pin_j     = [ latt.L,    0,         latt.L+1, 1        ]
pin_value = [ -hpin/2.0, -hpin/2.0, hpin/2.0, hpin/2.0 ]
K_i     = np.concatenate( [ latt_i, latt_i+latt.L, np.arange(latt.L), np.arange(latt.L)+latt.L, pin_i] )
K_j     = np.concatenate( [ latt_j, latt_j+latt.L, np.arange(latt.L), np.arange(latt.L)+latt.L, pin_j] )
K_value = np.concatenate( [ latt_hopping, latt_hopping, [ hz/2.0 - mu ]*latt.L, [ -hz/2.0 - mu ]*latt.L, pin_value ] )

#Write to file
f = open("model_param", 'w')
f.write( '{:16d} {:16d} \n'.format(2*latt.L, Ntot) )
f.write( '{:16d} \n'.format( len( K_value ) ) )
for i in range( len(K_value) ):
    f.write( '{:16d} {:16d} {:26.18e} {:26.18e} \n'.format( K_i[i], K_j[i], K_value[i].real,  K_value[i].imag ) )
f.write( '{:16d} \n'.format( latt.L ) )
for i in range( latt.L ):
    f.write( '{:16d} {:16d} {:16d} {:16d} {:26.18e} {:26.18e} \n'.format(i, i, i+latt.L, i+latt.L, U, 0) )
f.close()


matrixSize       = 20           #Lanczos matrix size
accuracy         = 1E-10        #when new b smaller than accuracy, converge
convergeFlag     = 'E'          #'E' or 'W', converge by wave function or energy
maxLoop          = 100          #The max Lanczos matrix loop
litForProjection = 0.01         #When b is smaller, we need to project wave function.
lanwfsFlag       = 'F'          #'R' or 'F', 'R' use recurse wf, 'F' store full Lanczos wf

f = open("lanczos_param", 'w')
f.write( '{:16d} \n'.format(matrixSize) )
f.write( '{:26.18e} \n'.format(accuracy)   )
f.write( '{:>16} \n'.format(convergeFlag))
f.write( '{:16d} \n'.format(maxLoop) )
f.write( '{:26.18e} \n'.format(litForProjection)   )
f.write( '{:>16} \n'.format(lanwfsFlag)   )
f.close()