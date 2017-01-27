import sys
import os
sys.path.append( os.environ['AFQMCLAB_DIR']+"/scripts/supercubic" )
from setHoping import *

latt_n  = [2,2]
ktwist  = [0.12,0.34]
tpp     = 0.7
tpd     = 1.2
ep      = -3.2
ed      = -7.6
Up      = 2.0
Ud      = 8.4
Nup     = 2
Ndn     = 2
UpDnFlag = 0    # 0 up=dn, 1 up=conj(dn) ==> different twist

#Set lattice information
latt = Latt_class( latt_n )

up_i =[]; up_j =[]; up_K=[];
for i in range( latt.L ):
    coor_i = latt.coor(i)

    # coor_j = coor_i
    j =i

    up_i.append(i);          up_j.append(j);            up_K.append(  ed  )   #d^{\dagger} d
    up_i.append(i);          up_j.append(j+latt.L);     up_K.append( -tpd )   #d^{\dagger} px
    up_i.append(i);          up_j.append(j+2*latt.L);   up_K.append(  tpd )   #d^{\dagger} py
    up_i.append(i+latt.L);   up_j.append(j+latt.L);     up_K.append(  ep  )   #px^{\dagger} px
    up_i.append(i+latt.L);   up_j.append(j);            up_K.append( -tpd )   #px^{\dagger} d
    up_i.append(i+latt.L);   up_j.append(j+2*latt.L);   up_K.append(  tpp )   #px^{\dagger} py
    up_i.append(i+2*latt.L); up_j.append(j+2*latt.L);   up_K.append(  ep  )   #py^{\dagger} py
    up_i.append(i+2*latt.L); up_j.append(j);            up_K.append(  tpd )   #py^{\dagger} d
    up_i.append(i+2*latt.L); up_j.append(j+latt.L);     up_K.append(  tpp )   #py^{\dagger} px

    #coor_j[0]=coor_i[0]-1
    coor_j=[ latt.bound( coor_i[0]-1, latt.n[0]  ),  coor_i[1] ]
    j = latt.index( coor_j )
    phase = np.exp( -1j * ktwist[0]*2.0*np.pi/latt.n[0] )

    up_i.append(i);          up_j.append(j+latt.L);     up_K.append( tpd*phase )   #d^{\dagger} px
    up_i.append(i+2*latt.L); up_j.append(j+latt.L);     up_K.append(-tpp*phase )   #py^{\dagger} px

    #coor_j[1]=coor_i[1]-1
    coor_j=[ coor_i[0],  latt.bound( coor_i[1]-1, latt.n[1]  ) ]
    j = latt.index( coor_j )
    phase = np.exp( -1j * ktwist[1]*2.0*np.pi/latt.n[1] )

    up_i.append(i);          up_j.append(j+2*latt.L);   up_K.append( -tpd*phase )   #d^{\dagger} py
    up_i.append(i+latt.L);   up_j.append(j+2*latt.L);   up_K.append( -tpp*phase )   #px^{\dagger} py

    #coor_j[0]=coor_i[0]+1
    coor_j=[ latt.bound( coor_i[0]+1, latt.n[0]  ),  coor_i[1] ]
    j = latt.index( coor_j )
    phase = np.exp( 1j * ktwist[0]*2.0*np.pi/latt.n[0] )

    up_i.append(i+latt.L);   up_j.append(j);            up_K.append( tpd*phase )   #px^{\dagger} d
    up_i.append(i+latt.L);   up_j.append(j+2*latt.L);   up_K.append(-tpp*phase )   #px^{\dagger} py

    #coor_j[1]=coor_i[1]+1
    coor_j=[ coor_i[0],  latt.bound( coor_i[1]+1, latt.n[1]  ) ]
    j = latt.index( coor_j )
    phase = np.exp( 1j * ktwist[1]*2.0*np.pi/latt.n[1] )

    up_i.append(i+2*latt.L); up_j.append(j);            up_K.append(-tpd*phase )   #py^{\dagger} d
    up_i.append(i+2*latt.L); up_j.append(j+latt.L);     up_K.append(-tpp*phase )   #py^{\dagger} px

    #coor_j[0]=coor_i[0]-1, coor_j[1]=coor_i[1]+1
    coor_j=[ latt.bound( coor_i[0]-1, latt.n[0]  ),  latt.bound( coor_i[1]+1, latt.n[1]  ) ]
    j = latt.index( coor_j )
    phase = np.exp( -1j * ktwist[0]*2.0*np.pi/latt.n[0] + 1j * ktwist[1]*2.0*np.pi/latt.n[1] )

    up_i.append(i+2*latt.L); up_j.append(j+latt.L);     up_K.append(  tpp*phase )   #py^{\dagger} px

    #coor_j[0]=coor_i[0]+1, coor_j[1]=coor_i[1]-1
    coor_j=[ latt.bound( coor_i[0]+1, latt.n[0]  ),  latt.bound( coor_i[1]-1, latt.n[1]  ) ]
    j = latt.index( coor_j )
    phase = np.exp( 1j * ktwist[0]*2.0*np.pi/latt.n[0] - 1j * ktwist[1]*2.0*np.pi/latt.n[1] )

    up_i.append(i+latt.L);   up_j.append(j+2*latt.L);   up_K.append(  tpp*phase )   #px^{\dagger} py

if UpDnFlag == 0:
    dn_i = up_i; dn_j = up_j; dn_K = up_K
elif UpDnFlag == 1:
    dn_i = up_i; dn_j = up_j; dn_K = np.conj(up_K)
else:
    print "WRONG!!! Do not know UpDnFlag!!!"
    sys.exit(1)

#Write to file
f = open("model_param", 'w')
f.write( '{:16d} {:16d} {:16d} \n'.format(3*latt.L, Nup, Ndn) )
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
f.write( '{:16d} \n'.format( 3*latt.L ) )
for i in range( latt.L ):
    f.write( '{:16d} {:16d} {:16d} {:16d} {:26.18e} {:26.18e} \n'.format(i, i, i, i, Ud, 0) )
for i in range( latt.L, 3*latt.L ):
    f.write( '{:16d} {:16d} {:16d} {:16d} {:26.18e} {:26.18e} \n'.format(i, i, i, i, Up, 0) )
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
