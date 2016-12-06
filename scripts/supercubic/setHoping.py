from lattClass import *
from copy import deepcopy

def HubbardNearestNeighborHopping(latt, k, t1):
    site_i = []; site_j = []; hopping = []
    for i in range(latt.L):
        coor_i = latt.coor(i)
        for dimenIndex in range(latt.dimen):
            for direct in [-1, 1]:
                coor_j = deepcopy( coor_i )
                coor_j[dimenIndex] = latt.bound( coor_i[dimenIndex]+direct, latt.n[dimenIndex]  )

                site_i.append( i )
                site_j.append( latt.index( coor_j ) )
                hopping.append( - t1 * np.exp( 1j * direct * k[dimenIndex]*2.0*np.pi/latt.n[dimenIndex] ) )
                
    return np.array(site_i), np.array(site_j), np.array(hopping)