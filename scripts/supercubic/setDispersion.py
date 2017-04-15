import subprocess
import os
from lattClass import *

#Set Hubbard_dispersion
def Hubbard_dispersion(latt, k, t1):
    ek = np.empty(latt.L);
    for i in range(latt.L):
        k_tmp = (latt.coor(i) + k)*2.0*np.pi/latt.n
        ek[i] = -2.0 * t1 * np.cos(k_tmp).sum()
    return ek

#Set Continous_dispersion
def Continous_dispersion(latt, k, t1):
    ek = np.empty(latt.L);
    for i in range(latt.L):
        k_tmp = (latt.coor(i) + k)*2.0*np.pi/latt.n
        k_tmp = np.arccos( np.cos(k_tmp) ) # k_tmp is (0, PI)
        ek[i] = t1 * (k_tmp*k_tmp).sum()
    return ek

def Hubbard_2Ddispersion(latt, k, t1, t2=0):
    if ( latt.dimen != 2 ):
        print ( "Error!!! Lattice dimension must be two!" )
        sys.exit(1)
    ek = np.empty(latt.L);
    for i in range(latt.L):
        k_tmp = (latt.coor(i) + k)*2.0*np.pi/latt.n
        ek[i] = -2.0*t1*np.cos(k_tmp).sum() -4.0*t2*np.cos(k_tmp[0])*np.cos(k_tmp[1])
    return ek

#Set Hubbard modify dispersion
def set_sort_list(ek):
    map_ek   = sorted( range(len(ek)), key=lambda k: ek[k] )
    ek_sort = ek[map_ek];

    ek_sort_unique = []; degeneracy = []; old_string = "dfdfdfdfdfdfdf"
    for number in ek_sort:
         new_string = '{:26.12e}'.format(number) if abs(number) > 1e-12 else '0.0000000000'
         if old_string != new_string:
             ek_sort_unique.append(number)
             degeneracy.append(1)
             old_string = new_string
         else:
             degeneracy[-1] +=1

    return map_ek, np.array(ek_sort_unique), np.array(degeneracy)

def Hubbard_modify_dispersion(latt, k, t1, n_inf):
    print ( "Set up modify dispersion for lattice, use ", ( n_inf/latt.n ) * latt.n )
    print ( "Make sure MBC disperson is close shell (Tune twist)! Otherwise, the result is not good." )

    #Set finite lattice
    ek = Hubbard_dispersion(latt, k, t1)
    map_ek, ek_sort_unique, degeneracy = set_sort_list(ek)
    
    #Set infinite lattice
    latt_inf    = Latt_class( ( n_inf/latt.n ) * latt.n );
    ek_inf_sort = np.sort( Hubbard_dispersion(latt_inf, k, t1) );
    degeneracy_inf = degeneracy * ( latt_inf.L / latt.L )
    if degeneracy_inf.sum() != latt_inf.L:
       print ( "Something is wrong with degeneracy_inf !" )
       sys.exit(1)
    
    #Reset ek_sort_unique
    len_ek_unique = len( ek_sort_unique );
    init_index  = 0
    for i in range(len_ek_unique):
        end_index         = init_index + degeneracy_inf[i]
        ek_sort_unique[i] = np.sum( ek_inf_sort[init_index:end_index] ) / degeneracy_inf[i]
        init_index        = end_index
    
    #Reset ek
    ek_index = 0
    for i in range(len_ek_unique):
        for j in range(degeneracy[i]):
            ek[ map_ek[ek_index] ] = ek_sort_unique[i]
            ek_index += 1

    return ek

#latt = Latt_class([4,4])
#ek = Hubbard_modify_dispersion(latt, [0.01,0.02], 1.0, 300)
#ek = np.sort(ek)
#print ( ek )
#print ( np.sum( ek[0:latt.L/2] )*2.0/latt.L )