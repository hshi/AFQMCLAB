import os
import sys; sys.path.append( os.environ['AFQMCLAB_DIR']+"/scripts/pyscf" )
from molecule import *

atoms             = [['O',(0.000,0.000,0.000)]]
chrg              = 1
spn               = 3
basis             = 'bfd-vdz'
psp               = 'bfd-pp'
sym               = 'c1'

mol = setupMolecule(atoms, chrg, spn, basis, psp, sym)
rhf  = doROHFCalculation(mol, 1e-5, 16000, 5000)
canonic = CanonicalBais(mol, rhf, 1e-8)

writeInputForModel(mol, rhf, canonic, 1e-12)
writeROHFSD2is(mol, rhf, canonic, "phi.dat")
writeROHFSD2s(mol, rhf, canonic, "phiT.dat")

# Is this FCI, why not in PySCF website? Where is the manual?
from  pyscf  import fci
cisolver = fci.FCI(mol, rhf.mo_coeff)
print ( cisolver.kernel()[0] )

#Check pop control and Modfied GS
