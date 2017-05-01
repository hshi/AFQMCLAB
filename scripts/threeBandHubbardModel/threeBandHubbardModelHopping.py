import sys
import os
sys.path.append( os.environ['AFQMCLAB_DIR']+"/scripts/supercubic" )
from lattClass import *

def threeBandHubbardModelRectangularHopping(latt, ktwist, tpp, tpd, ep, ed):
    site_i =[]; site_j =[]; hopping=[];
    for i in range( latt.L ):
        coor_i = latt.coor(i)

        # coor_j = coor_i
        j =i

        site_i.append(i);          site_j.append(j);            hopping.append(  ed  )   #d^{\dagger} d
        site_i.append(i);          site_j.append(j+latt.L);     hopping.append( -tpd )   #d^{\dagger} px
        site_i.append(i);          site_j.append(j+2*latt.L);   hopping.append(  tpd )   #d^{\dagger} py
        site_i.append(i+latt.L);   site_j.append(j+latt.L);     hopping.append(  ep  )   #px^{\dagger} px
        site_i.append(i+latt.L);   site_j.append(j);            hopping.append( -tpd )   #px^{\dagger} d
        site_i.append(i+latt.L);   site_j.append(j+2*latt.L);   hopping.append(  tpp )   #px^{\dagger} py
        site_i.append(i+2*latt.L); site_j.append(j+2*latt.L);   hopping.append(  ep  )   #py^{\dagger} py
        site_i.append(i+2*latt.L); site_j.append(j);            hopping.append(  tpd )   #py^{\dagger} d
        site_i.append(i+2*latt.L); site_j.append(j+latt.L);     hopping.append(  tpp )   #py^{\dagger} px

        #coor_j[0]=coor_i[0]-1
        coor_j=[ latt.bound( coor_i[0]-1, latt.n[0]  ),  coor_i[1] ]
        j = latt.index( coor_j )
        phase = np.exp( -1j * ktwist[0]*2.0*np.pi/latt.n[0] )

        site_i.append(i);          site_j.append(j+latt.L);     hopping.append( tpd*phase )   #d^{\dagger} px
        site_i.append(i+2*latt.L); site_j.append(j+latt.L);     hopping.append(-tpp*phase )   #py^{\dagger} px

        #coor_j[1]=coor_i[1]-1
        coor_j=[ coor_i[0],  latt.bound( coor_i[1]-1, latt.n[1]  ) ]
        j = latt.index( coor_j )
        phase = np.exp( -1j * ktwist[1]*2.0*np.pi/latt.n[1] )

        site_i.append(i);          site_j.append(j+2*latt.L);   hopping.append( -tpd*phase )   #d^{\dagger} py
        site_i.append(i+latt.L);   site_j.append(j+2*latt.L);   hopping.append( -tpp*phase )   #px^{\dagger} py

        #coor_j[0]=coor_i[0]+1
        coor_j=[ latt.bound( coor_i[0]+1, latt.n[0]  ),  coor_i[1] ]
        j = latt.index( coor_j )
        phase = np.exp( 1j * ktwist[0]*2.0*np.pi/latt.n[0] )

        site_i.append(i+latt.L);   site_j.append(j);            hopping.append( tpd*phase )   #px^{\dagger} d
        site_i.append(i+latt.L);   site_j.append(j+2*latt.L);   hopping.append(-tpp*phase )   #px^{\dagger} py

        #coor_j[1]=coor_i[1]+1
        coor_j=[ coor_i[0],  latt.bound( coor_i[1]+1, latt.n[1]  ) ]
        j = latt.index( coor_j )
        phase = np.exp( 1j * ktwist[1]*2.0*np.pi/latt.n[1] )

        site_i.append(i+2*latt.L); site_j.append(j);            hopping.append(-tpd*phase )   #py^{\dagger} d
        site_i.append(i+2*latt.L); site_j.append(j+latt.L);     hopping.append(-tpp*phase )   #py^{\dagger} px

        #coor_j[0]=coor_i[0]-1, coor_j[1]=coor_i[1]+1
        coor_j=[ latt.bound( coor_i[0]-1, latt.n[0]  ),  latt.bound( coor_i[1]+1, latt.n[1]  ) ]
        j = latt.index( coor_j )
        phase = np.exp( -1j * ktwist[0]*2.0*np.pi/latt.n[0] + 1j * ktwist[1]*2.0*np.pi/latt.n[1] )

        site_i.append(i+2*latt.L); site_j.append(j+latt.L);     hopping.append(  tpp*phase )   #py^{\dagger} px

        #coor_j[0]=coor_i[0]+1, coor_j[1]=coor_i[1]-1
        coor_j=[ latt.bound( coor_i[0]+1, latt.n[0]  ),  latt.bound( coor_i[1]-1, latt.n[1]  ) ]
        j = latt.index( coor_j )
        phase = np.exp( 1j * ktwist[0]*2.0*np.pi/latt.n[0] - 1j * ktwist[1]*2.0*np.pi/latt.n[1] )

        site_i.append(i+latt.L);   site_j.append(j+2*latt.L);   hopping.append(  tpp*phase )   #px^{\dagger} py

    return np.array(site_i), np.array(site_j), np.array(hopping)