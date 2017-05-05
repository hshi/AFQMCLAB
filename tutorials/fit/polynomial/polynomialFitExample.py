import os
import numpy as np
import sys; sys.path.append( os.environ['AFQMCLAB_DIR']+"/scripts/fit" )
import polynomial

x,y=np.loadtxt("data", unpack=True)
popt,perr=polynomial.fit(2, x, y)
polynomial.plot(popt, x, y)