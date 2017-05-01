import sys
import os
import subprocess
sys.path.append( os.environ['AFQMCLAB_DIR']+"/scripts/threeBandHubbardModel" )
from threeBandHubbardModelHopping import *

latt_n  = [8,8]
ktwist  = [0.12,0.34]
tpp     = 0.7
tpd     = 1.2
ep      = -3.2
ed      = -7.6
Up      = 0 #2.0
Ud      = 0 #8.4
Ntot    = 64
UpDnFlag = 0    # 0 up=dn, 1 up=conj(dn) ==> different twist

#Set lattice information
latt = Latt_class( latt_n )
latt.write("latt_param")

up_i, up_j, up_K = threeBandHubbardModelRectangularHopping(latt, ktwist, tpp, tpd, ep, ed)
if UpDnFlag == 0:
    dn_i = up_i; dn_j = up_j; dn_K = up_K
elif UpDnFlag == 1:
    dn_i = up_i; dn_j = up_j; dn_K = np.conj(up_K)
else:
    print ( "WRONG!!! Do not know UpDnFlag!!!" )
    sys.exit(1)

Kmatrix = np.zeros( (6*latt.L, 6*latt.L), dtype='complex', order='F' )
for i in range( len(up_K) ):
    Kmatrix[ up_i[i], up_j[i] ] += up_K[i]
for i in range( len(dn_K) ):
    Kmatrix[ dn_i[i]+3*latt.L, dn_j[i]+3*latt.L ] += dn_K[i]

f = open("model_param", 'w')
f.write( '{:16d} \n'.format(3*latt.L) )
f.write( '{:16d} \n'.format(Ntot) )
for i in range( 6*latt.L ):
    for j in range( 6*latt.L ):
        f.write( '{:26.18e} {:26.18e} \n'.format( Kmatrix[j,i].real,  Kmatrix[j,i].imag ) )
for i in range( 3*latt.L ):
    f.write( '{:26.18e} \n'.format( 0.0 ) )  #mu
for i in range( 3*latt.L ):
    f.write( '{:26.18e} \n'.format( 0.0 ) )  #hx
for i in range( 3*latt.L ):
    f.write( '{:26.18e} \n'.format( 0.0 ) )  #hy
for i in range( 3*latt.L ):
    f.write( '{:26.18e} \n'.format( 0.0 ) )  #hz
for i in range( latt.L ):
    f.write( '{:26.18e} \n'.format( Ud ) )
for i in range( 2*latt.L ):
    f.write( '{:26.18e} \n'.format( Up ) )
f.close()

#Method Parameter
initialType               =  "readOrderParameter"  # "setFromModel", "readWaveFunction", "readOrderParameter"
convergeType              =  "energy"        # "energy", "orderParameter"
convergeTolerance         =  1e-12
maxIterateStep            =  10000
annealMagnitude           =  0.3
annealStep                =  0
relaxMagnitude            =  0.5          # 1.0 fully relax to new order paramter, 0.0 not update
seed                      =  985456376    # 1. read file, 0. random, else is seeds
initOrderParamType        =  "xafm"       # None, zafm, xafm, yafm, random

#write method_param
f = open('ghf_param', 'w')
f.write(   '{:>26} \n'.format(initialType       ) )
f.write(   '{:>26} \n'.format(convergeType      ) )
f.write('{:26.18e} \n'.format(convergeTolerance ) )
f.write(   '{:26d} \n'.format(maxIterateStep    ) )
f.write('{:26.18e} \n'.format(annealMagnitude   ) )
f.write(   '{:26d} \n'.format(annealStep        ) )
f.write('{:26.18e} \n'.format(relaxMagnitude    ) )
f.write(   '{:26d} \n'.format(seed              ) )
f.close()

#Run script to generate orderParameter file.
pythonFileDir =  os.path.dirname(os.path.realpath(__file__))
if initOrderParamType is not None:
    subprocess.call( "python {0}/initialOrderParameter.py {1}".format(pythonFileDir, initOrderParamType),shell=True)
