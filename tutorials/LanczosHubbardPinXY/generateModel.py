import sys
import os
sys.path.append( os.environ['AFQMC_DIR']+"/scripts/supercubic" )
from setHoping import *

latt_n   = [3,4]
ktwist   = [0.12,0.36]
t1       = 1.0
U        = 4.0
mu       = 0 #2.0
hz       = 0 #1.87246
hpin     = 0 #2.0
Ntot     = 4

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
