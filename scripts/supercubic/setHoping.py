from lattClass import *
from copy import deepcopy

def HubbardNearestNeighborHopping(latt, k, t1):
    theta = np.array(k)*2.0*np.pi/latt.n
    site_i = []; site_j = []; hopping = []
    for i in range(latt.L):
        coor_i = latt.coor(i)
        for dimenIndex in range(latt.dimen):
            for direct in [-1, 1]:
                coor_j = deepcopy( coor_i )
                coor_j[dimenIndex] = latt.bound( coor_i[dimenIndex]+direct, latt.n[dimenIndex]  )

                site_i.append( i )
                site_j.append( latt.index( coor_j ) )
                hopping.append( - t1 * np.exp( 1j * direct * theta[dimenIndex] ) )
                
    return np.array(site_i), np.array(site_j), np.array(hopping)

def HubbardNearestNeighborHoppingOpenOneDimension(latt, k, t1, openD=0):
    theta = np.array(k)*2.0*np.pi/latt.n
    site_i = []; site_j = []; hopping = []
    for i in range(latt.L):
        coor_i = latt.coor(i)
        for direct in [-1, 1]:
            for dimenIndex in range(latt.dimen):
                coor_j = deepcopy( coor_i )
                if dimenIndex==openD:
                    newCoor = latt.boundOpen( coor_i[dimenIndex]+direct, latt.n[dimenIndex]  )
                    if  newCoor is not None:
                       coor_j[dimenIndex] = newCoor
                       site_i.append( i )
                       site_j.append( latt.index( coor_j ) )
                       hopping.append( - t1  )
                else:
                    coor_j[dimenIndex] = latt.bound( coor_i[dimenIndex]+direct, latt.n[dimenIndex]  )
                    site_i.append( i )
                    site_j.append( latt.index( coor_j ) )
                    hopping.append( - t1 * np.exp( 1j * direct * theta[dimenIndex] ) )
    return np.array(site_i), np.array(site_j), np.array(hopping)

def Hubbard2DNextNearestNeighborHopping(latt, k, t2):
    if ( latt.dimen != 2 ):
        print ( "Error!!! Lattice dimension must be two!" )
        sys.exit(1)

    theta = np.array(k)*2.0*np.pi/latt.n
    site_i = []; site_j = []; hopping = []
    coor_j = [0,0]
    for i in range(latt.L):
        coor_i = latt.coor(i)
        for direct_x in [-1, 1]:
            for direct_y in [-1, 1]:
                coor_j[0] = latt.bound( coor_i[0]+direct_x, latt.n[0]  )
                coor_j[1] = latt.bound( coor_i[1]+direct_y, latt.n[1]  )
                site_i.append( i )
                site_j.append( latt.index( coor_j ) )
                hopping.append( - t2 * np.exp( 1j*direct_x* theta[0] + 1j*direct_y*theta[1] ) )

    return np.array(site_i), np.array(site_j), np.array(hopping)

def Hubbard2DNextNearestNeighborHoppingOpenX(latt, k, t2):
    if ( latt.dimen != 2 ):
        print ( "Error!!! Lattice dimension must be two!" )
        sys.exit(1)

    theta = np.array(k)*2.0*np.pi/latt.n
    site_i = []; site_j = []; hopping = []
    coor_j = [0,0]
    for i in range(latt.L):
        coor_i = latt.coor(i)
        for direct_x in [-1, 1]:
            for direct_y in [-1, 1]:
                newCoor   = latt.boundOpen( coor_i[0]+direct_x, latt.n[0]  )
                coor_j[1] = latt.bound( coor_i[1]+direct_y, latt.n[1]  )
                if newCoor is not None:
                    coor_j[0] = newCoor
                    site_i.append( i )
                    site_j.append( latt.index( coor_j ) )
                    hopping.append( - t2 * np.exp( 1j*direct_y*theta[1] ) )

    return np.array(site_i), np.array(site_j), np.array(hopping)

def Hubbard2DNextNearestNeighborHoppingOpenY(latt, k, t2):
    if ( latt.dimen != 2 ):
        print ( "Error!!! Lattice dimension must be two!" )
        sys.exit(1)

    theta = np.array(k)*2.0*np.pi/latt.n
    site_i = []; site_j = []; hopping = []
    coor_j = [0,0]
    for i in range(latt.L):
        coor_i = latt.coor(i)
        for direct_x in [-1, 1]:
            for direct_y in [-1, 1]:
                coor_j[0] = latt.bound( coor_i[0]+direct_x, latt.n[0]  )
                newCoor  = latt.boundOpen( coor_i[1]+direct_y, latt.n[1]  )
                if newCoor is not None:
                    coor_j[1] = newCoor
                    site_i.append( i )
                    site_j.append( latt.index( coor_j ) )
                    hopping.append( - t2 * np.exp( 1j*direct_x* theta[0] ) )

    return np.array(site_i), np.array(site_j), np.array(hopping)

def Hubbard2DColumnAFMPinning(latt, column, pin):
    if ( latt.dimen != 2 ):
        print ( "Error!!! Lattice dimension must be two!" )
        sys.exit(1)

    site_i = []; site_j = []; hopping = []
    for i in range(latt.L):
        coor_i = latt.coor(i)
        if( coor_i[0] == column ):
            site_i.append( i )
            site_j.append( i )
            hopping.append( (-1)**coor_i[1] * pin )

    return np.array(site_i), np.array(site_j), np.array(hopping)

def Hubbard2DRowAFMPinning(latt, row, pin):
    if ( latt.dimen != 2 ):
        print ( "Error!!! Lattice dimension must be two!" )
        sys.exit(1)

    site_i = []; site_j = []; hopping = []
    for i in range(latt.L):
        coor_i = latt.coor(i)
        if( coor_i[1] == row ):
            site_i.append( i )
            site_j.append( i )
            hopping.append( (-1)**coor_i[0] * pin )

    return np.array(site_i), np.array(site_j), np.array(hopping)