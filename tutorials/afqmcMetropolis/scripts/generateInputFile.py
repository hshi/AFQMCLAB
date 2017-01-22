import sys
import os
sys.path.append( os.environ['AFQMCLAB_DIR']+"/scripts/supercubic" )
from setHoping import *

#Model Parameter
latt_n   = [3,3]
ktwist   = [0.12,0.34]
t1       = 1.0
U        = -4.0
mu       = 2.0
Ntot     = 10
UpDnFlag = 1    # 0 up=dn, 1 up=conj(dn) ==> different twist

#Set lattice information
latt = Latt_class( latt_n )
up_i, up_j, up_K = HubbardNearestNeighborHopping(latt, ktwist, t1)
if UpDnFlag == 0:
    dn_i = up_i; dn_j = up_j; dn_K = up_K
elif UpDnFlag == 1:
    dn_i, dn_j, dn_K = HubbardNearestNeighborHopping(latt, -np.array(ktwist), t1)
else:
    print "WRONG!!! Do not know UpDnFlag!!!"
    sys.exit(1)

Kmatrix = np.zeros( (2*latt.L, 2*latt.L), dtype='complex', order='F' )
for i in range( len(up_K) ):
    Kmatrix[ up_i[i], up_j[i] ] = up_K[i]
for i in range( len(dn_K) ):
    Kmatrix[ dn_i[i]+latt.L, dn_j[i]+latt.L ] = dn_K[i]

f = open("model_param", 'w')
f.write( '{:16d} \n'.format(latt.L) )
f.write( '{:16d} \n'.format(Ntot) )
for i in range( 2*latt.L ):
    for j in range( 2*latt.L ):
       f.write( '{:26.18e} {:26.18e} \n'.format( Kmatrix[j,i].real,  Kmatrix[j,i].imag ) )
for i in range( latt.L ):
    f.write( '{:26.18e} \n'.format( mu ) )
for i in range( latt.L ):
    f.write( '{:26.18e} \n'.format( 0.0 ) )  #hx
for i in range( latt.L ):
    f.write( '{:26.18e} \n'.format( 0.0 ) )  #hy
for i in range( latt.L ):
    f.write( '{:26.18e} \n'.format( 0.0 ) )  #hz
for i in range( latt.L ):
    f.write( '{:26.18e} \n'.format( U ) )
f.close()


#Method Parameter
dt                        =  0.01
decompType                =  "densityCharge" # "densityCharge", "densitySpin", "hopCharge", "hopSpin"
forceType                 =  "dynamicForce"  # "dynamicForce", "constForce"
sampleCap                 =  1.0
thermalSweep              =  10
measureSweep              =  50
writeSweep                =  2
stabilizeStep             =  10
timesliceSize             =  6400
timesliceBlockSize        =  40
initalWalkerFlag          =  "setFromModel"  #"setFromModel", "setRandomly", "readFromFile"
initalAuxiliaryFlag       =  "dynamicForceInitial" #"dynamicForceInitial", "constForceInitial", "readFromFile"
measureType               =  "commute"  #"commute", "observable"
measureVarianceType       =  "normal"   #"normal", "fixVariance"
measureSkipTimesliceStep  =  20
measureSkipTimesliceLeft  =  0
measureSkipTimesliceRight =  0
seed                      =  985456376  # -1. read file, 0. random, else is seeds

#write method_param
f = open('afqmc_param', 'w')
f.write('{:26.18e} \n'.format(dt                       ) )
f.write(   '{:>26} \n'.format(decompType               ) )
f.write(   '{:>26} \n'.format(forceType                ) )
f.write('{:26.18e} \n'.format(sampleCap                ) )
f.write(   '{:26d} \n'.format(thermalSweep             ) )
f.write(   '{:26d} \n'.format(measureSweep             ) )
f.write(   '{:26d} \n'.format(writeSweep               ) )
f.write(   '{:26d} \n'.format(stabilizeStep            ) )
f.write(   '{:26d} \n'.format(timesliceSize            ) )
f.write(   '{:26d} \n'.format(timesliceBlockSize       ) )
f.write(   '{:>26} \n'.format(initalWalkerFlag         ) )
f.write(   '{:>26} \n'.format(initalAuxiliaryFlag      ) )
f.write(   '{:>26} \n'.format(measureType              ) )
f.write(   '{:>26} \n'.format(measureVarianceType      ) )
f.write(   '{:26d} \n'.format(measureSkipTimesliceStep ) )
f.write(   '{:26d} \n'.format(measureSkipTimesliceLeft ) )
f.write(   '{:26d} \n'.format(measureSkipTimesliceRight) )
f.write(   '{:26d} \n'.format(seed                     ) )
f.close()

#write constForce_param
f = open('constForce_param', 'w')
for i in range( latt.L ):
    f.write( '{:26.18e} \n'.format( 0.0 ) )
f.close()
