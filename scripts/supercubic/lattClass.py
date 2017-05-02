import numpy as np
import sys

#Input a float array, remove duplicate elements, and sort the array, return the final array
def sort_unique_array(old_array_float):
    array_string = ['{:26.12e}'.format(number) for number in old_array_float]
    array_string = np.unique( array_string )
    new_array_float = [float(each_string) for each_string in array_string]
    new_array_float = sorted( new_array_float )
    return new_array_float

#Input a symmetry array and a origin array, return a index list map origin array to symmetry array
def create_index_list(sym_array_float, origin_array_float):
    origin_array_string = ['{:26.12e}'.format(number) for number in origin_array_float]
    sym_array_string    = ['{:26.12e}'.format(number) for number in sym_array_float]
    index_list = [ sym_array_string.index(each_string) for each_string in origin_array_string ]
    return index_list

class Latt_class:

    def __init__(self, n):

        self.dimen = len(n)

        L = 1
        for i in n:
            L*=i
        self.L=L

        self.n=np.array(n)

    @classmethod
    def read(cls, filename):
        f          =  open(filename, 'r')
        lines_list =  f.readlines()

        dimen =  int(lines_list[0].split()[0])

        n     =  []
        linetmp    =  lines_list[1].split()
        for i in range(dimen):
            n.append( int(linetmp[i]) )
        f.close()

        return cls(n) 

    def write(self, filename):
        ndat=''
        for i in self.n:
            ndat += ( '{:d} '.format(i) )
        ndat += "\n"
        f = open(filename, 'w')
        f.write( '{:d} \n'.format(self.dimen) )
        f.write(  ndat                        )
        f.close()

    def coor(self, index):
        den=self.L; coor=np.empty(self.dimen, dtype=int)
        for i in range(self.dimen-1, -1, -1):
            den/=self.n[i]
            coor[i]=index/den
            index%=den
        return coor

    def index(self, coor):
        if(len(coor)!=self.dimen):
           print ( "WRONG!!! Lens of coor is differnt with latt dimension!" )
           sys.exit(1)
        lattice_index=0; den=1
        for i in range(self.dimen):
            lattice_index+=(coor[i]*den)
            den*=self.n[i]
        return lattice_index

    def r_distance(self, coor):
        return np.linalg.norm(coor)

    def k_distance(self, coor):
        k_coor = coor*2.0*np.pi/self.n
        return np.linalg.norm(k_coor) 

    def bound(self, i, i_max):
        return i%i_max

    def boundOpen(self, i, i_max):
        if i >= i_max:
            return None
        elif i < 0:
            return None
        else:
            return i%i_max

    #return coor_j - coor_i
    def coor_relat(self, coor_i, coor_j):
        coor=np.empty(self.dimen, dtype=int)
        for i in range(self.dimen):
            coor[i] = self.bound(coor_j[i]-coor_i[i], self.n[i])
        return coor

    #return min( coor_j - coor_i, coor_i -coor_j )
    def coor_abs_relat(self, coor_i, coor_j):
        coor=np.empty(self.dimen, dtype=int)
        for i in range(self.dimen):
            dist1   = self.bound(coor_i[i]-coor_j[i], self.n[i])
            dist2   = self.bound(coor_j[i]-coor_i[i], self.n[i])
            coor[i] = min(dist1, dist2)
        return coor

    #Return r symmetry distance, and list map to it 
    def r_symmetry(self):
        index_0 = self.coor(0)
        r_full = []
        for i in range(self.L):
            index_i   = self.coor(i)
            index_abs = self.coor_abs_relat(index_0, index_i)
            r_full.append ( self.r_distance( index_abs ) )
        r_sym = sort_unique_array( r_full )
        index_list = create_index_list( r_sym, r_full ) 
        return r_sym, index_list

    #Return k symmetry distance, and list map to it 
    def k_symmetry(self):
        index_0 = self.coor(0)
        k_full = []
        for i in range(self.L):
            index_i   = self.coor(i)
            index_abs = self.coor_abs_relat(index_0, index_i)
            k_full.append ( self.k_distance( index_abs ) )
        k_sym = sort_unique_array( k_full )
        index_list = create_index_list( k_sym, k_full )
        return k_sym, index_list