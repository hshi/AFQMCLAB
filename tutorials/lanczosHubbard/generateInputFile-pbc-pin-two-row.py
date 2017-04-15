import sys
import os
sys.path.append( os.environ['AFQMCLAB_DIR']+"/scripts/supercubic" )
from setHoping import *

latt_n  =  [4,4]
ktwist  =  [0.0,0.0]
t1      =  1.0
t2      =  0.2
pin_0   =  0.25
pin_L   = -0.25
U       =  8.0
Nup     =  5
Ndn     =  5
UpDnFlag = 0    # 0 up=dn, 1 up=conj(dn) ==> different twist

#Set lattice information
latt = Latt_class( latt_n )
up_i, up_j, up_K = HubbardNearestNeighborHopping(latt, ktwist, t1)
if( abs(t2) > 1e-10 ):
    up_i_p, up_j_p, up_K_p = Hubbard2DNextNearestNeighborHopping(latt, ktwist, t2)
    up_i = np.concatenate([up_i, up_i_p])
    up_j = np.concatenate([up_j, up_j_p])
    up_K = np.concatenate([up_K, up_K_p])
if( abs(pin_0) > 1e-10 ):
    up_i_p, up_j_p, up_K_p = Hubbard2DRowAFMPinning(latt, 0, pin_0)
    up_i = np.concatenate([up_i, up_i_p])
    up_j = np.concatenate([up_j, up_j_p])
    up_K = np.concatenate([up_K, up_K_p])
if( abs(pin_L) > 1e-10 ):
    up_i_p, up_j_p, up_K_p = Hubbard2DRowAFMPinning(latt, latt_n[1]-1, pin_L)
    up_i = np.concatenate([up_i, up_i_p])
    up_j = np.concatenate([up_j, up_j_p])
    up_K = np.concatenate([up_K, up_K_p])

if UpDnFlag == 0:
    dn_i = up_i; dn_j = up_j; dn_K = up_K
elif UpDnFlag == 1:
    dn_i = up_i; dn_j = up_j; dn_K = np.conj( up_K )
else:
    print ( "WRONG!!! Do not know UpDnFlag!!!" )
    sys.exit(1)

#Write to file
f = open("model_param", 'w')
f.write( '{:16d} {:16d} {:16d} \n'.format(latt.L, Nup, Ndn) )
#for up
f.write( '{:16d} \n'.format( len( up_K ) ) )
for i in range( len(up_K) ):
    f.write( '{:16d} {:16d} {:26.18e} {:26.18e} \n'.format( up_i[i], up_j[i], up_K[i].real,  up_K[i].imag ) )
#for dn
f.write( '{:16d} \n'.format( len( dn_K ) ) )
for i in range( len(dn_K) ):
    f.write( '{:16d} {:16d} {:26.18e} {:26.18e} \n'.format( dn_i[i], dn_j[i], dn_K[i].real,  dn_K[i].imag ) )
#for upUp
f.write( '{:16d} \n'.format( 0 ) )
#for upDn
f.write( '{:16d} \n'.format( latt.L ) )
for i in range( latt.L ):
    f.write( '{:16d} {:16d} {:16d} {:16d} {:26.18e} {:26.18e} \n'.format(i, i, i, i, U, 0) )
#for dnDn
f.write( '{:16d} \n'.format( 0 ) )
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


#Test
#Hzero = np.zeros(( latt.L, latt.L), dtype=complex )
#for i in range( len(up_K) ):
#    Hzero[ up_i[i], up_j[i] ] += up_K[i]
#print ( np.real( np.sort( np.linalg.eig(Hzero)[0] ) ) )
