import numpy as np
import sys
import h5py
import pyscf
from   pyscf  import ao2mo, gto, scf

def setupMolecule(atoms=None,chrg=None,spn=None,basis=None,psp=None,sym=None):

    mol          = pyscf.gto.Mole()
    mol.verbose  = 4
    mol.output   = 'mole.dat'
    mol.atom     = atoms
    mol.charge   = chrg
    mol.spin     = spn
    mol.basis    = basis
    mol.symmetry = sym
    mol.ecp      = psp
    mol.unit     = 'Bohr'
    mol.build()

    Enuc    = gto.energy_nuc(mol)
    nbasis  = mol.nao_nr()
    nelec_a = (mol.nelectron+mol.spin)//2
    nelec_b = (mol.nelectron-mol.spin)//2

    print('Molecule [geometry in Bohr]')
    print atoms

    print('Nuclear repulsion energy = {:26.18e} '.format(Enuc))

    print('AO basis ',basis)
    basis_label = gto.spheric_labels(mol)
    for index, item in enumerate( basis_label ):
        print( "{:<9} {:<16}".format(index, item) )

    print('charge          {:>9d}'.format(chrg)   )
    print('spin            {:>9d}'.format(spn)    )
    print('orbitals        {:>9d}'.format(nbasis) )
    print('alpha electrons {:>9d}'.format(nelec_a))
    print('beta  electrons {:>9d}'.format(nelec_b))

    return mol

def doROHFCalculation(mol=None, conv=1e-5, maxMem=16000, maxCycle=5000):

    if( mol.spin== 0 ):
        rhf = scf.ROHF(mol)
    else:
        rhf = scf.RHF(mol)

    rhf.conv_tol   = conv
    rhf.max_memory = maxMem
    rhf.max_cycle  = maxCycle
    rhf.kernel()
    print( 'Total RHF energy = {:26.18e}'.format(rhf.energy_tot()) )

    return rhf

class CanonicalBais:

    def __init__(self, mol, rhf, tol=1e-8):

        self.nbasis = mol.nao_nr()
        ovlp   = rhf.get_ovlp()

        value, vector = np.linalg.eigh( ovlp )
        print( "Eigenvalue of overlap matrix: " )
        for index, item in enumerate( value ):
            print( "{:<9} {:26.18e}".format(index, item) )

        if( tol >= value[-1] ):
            print("Error!!! Tol = {}, too big for determining the dependency!".format(tol))
            sys.exit(1)
        numberOfDependent = next(i for i, v in enumerate(value) if v > tol)

        print( "Number of dependent obritals is {}.".format(numberOfDependent) )
        self.L = self.nbasis - numberOfDependent

        value = value[numberOfDependent:self.nbasis]
        vector = vector[:,numberOfDependent:self.nbasis]
        sqrtValue = np.sqrt(value)
        self.X = vector / sqrtValue
        self.XInv = vector.T * sqrtValue[:, None]
        self.XT = self.X.T

def getCholeskyAO(mol=None, tol=1e-5):

    nbasis  = mol.nao_nr()
    eri = scf._vhf.int2e_sph(mol._atm,mol._bas,mol._env)
    V   = ao2mo.restore(1, eri, nbasis)
    V   = V.reshape( nbasis*nbasis, nbasis*nbasis )

    choleskyVecAO = []; choleskyNum = 0
    Vdiag = V.diagonal().copy()
    while True:
        imax = np.argmax(Vdiag); vmax = Vdiag[imax]
        print( "Inside modified Cholesky {:<9} {:26.18e}.".format(choleskyNum, vmax) )
        if(vmax<tol):
            print( "Number of Cholesky fields is {:9}".format(choleskyNum) )
            break
        else:
            oneVec = V[imax]/np.sqrt(vmax)
            choleskyVecAO.append( oneVec )
            choleskyNum+=1
            V -= np.dot(oneVec[:, None], oneVec[None,:])
            Vdiag -= oneVec**2

    return choleskyNum, choleskyVecAO

def getCholeskyMO(mol=None, canonic=None, tol=1e-5):

    nbasis  = mol.nao_nr()
    choleskyNum, choleskyVecAO = getCholeskyAO(mol, tol)

    choleskyVecMO = np.zeros((choleskyNum, canonic.L*canonic.L))
    for i in range(choleskyNum):
        oneVec = choleskyVecAO[i].reshape(nbasis, nbasis)
        choleskyVecMO[i] = np.dot( canonic.XT, np.dot( oneVec, canonic.X ) ).ravel()

    return choleskyNum, choleskyVecMO

def writeInputForModel(mol=None, rhf=None, canonic=None, tol=1e-5):

    Nup = (mol.nelectron+mol.spin)//2
    Ndn = (mol.nelectron-mol.spin)//2

    choleskyNum, choleskyVecMO = getCholeskyMO(mol, canonic, tol)
    t = np.dot( canonic.XT, np.dot( rhf.get_hcore(), canonic.X ) )
    K = t.copy()
    for i in range(choleskyNum):
        oneVec = choleskyVecMO[i].reshape(canonic.L, canonic.L)
        K += (-0.5)*np.dot( oneVec, oneVec )

    f = h5py.File("model_param", "w")
    f.create_dataset("L",              (1,),                        data=[canonic.L],           dtype='int')
    f.create_dataset("Nup",            (1,),                        data=[Nup],                 dtype='int')
    f.create_dataset("Ndn",            (1,),                        data=[Ndn],                 dtype='int')
    f.create_dataset("choleskyNumber", (1,),                        data=[choleskyNum],         dtype='int')
    f.create_dataset("t",              (canonic.L**2,),             data=t.ravel(),             dtype='float')
    f.create_dataset("K",              (canonic.L**2,),             data=K.ravel(),             dtype='float')
    f.create_dataset("choleskyVecs",   (choleskyNum*canonic.L**2,), data=choleskyVecMO.ravel(), dtype='float')
    f.create_dataset("choleskyBg",     (choleskyNum,),              data=np.zeros(choleskyNum), dtype='float')
    f.close()

def writeROHFSD2is(mol=None, rhf=None, canonic=None, filename=None):

    Nup  = (mol.nelectron+mol.spin)//2
    Ndn  = (mol.nelectron-mol.spin)//2
    maxN = max(Nup, Ndn)

    wf = rhf.mo_coeff[:, 0:maxN]
    wf = np.dot( canonic.XInv, wf )
    f = open(filename, 'w')
    f.write('{:26.18e} {:26.18e} \n'.format(0.0,0.0))
    f.write('{:26d} \n'.format(Nup ))
    f.write('{:26d} \n'.format(Ndn ))

    f.write('{:26d} \n'.format(2))
    f.write('{:26d} {:26d} \n'.format(canonic.L,maxN))
    for i in range(maxN):
        for j in range(canonic.L):
            f.write( '{:26.18e} {:26.18e} \n'.format(wf[j,i],0.0))
    f.close()

def writeROHFSD2s(mol=None, rhf=None, canonic=None, filename=None):

    Nup = (mol.nelectron+mol.spin)//2
    Ndn = (mol.nelectron-mol.spin)//2

    wf = rhf.mo_coeff[:, 0:max(Nup, Ndn)]
    wf = np.dot( canonic.XInv, wf )
    f = open(filename, 'w')

    f.write('{:26.18e} {:26.18e} \n'.format(0.0,0.0))

    f.write('{:26d} \n'.format(2))
    f.write('{:26d} {:26d} \n'.format(canonic.L,Nup))
    for i in range(Nup):
        for j in range(canonic.L):
            f.write( '{:26.18e} {:26.18e} \n'.format(wf[j,i],0.0))

    f.write('{:26d} \n'.format(2))
    f.write('{:26d} {:26d} \n'.format(canonic.L,Ndn))
    for i in range(Ndn):
        for j in range(canonic.L):
            f.write( '{:26.18e} {:26.18e} \n'.format(wf[j,i],0.0))
    f.close()
