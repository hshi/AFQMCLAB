import os
import numpy as np
import sys; sys.path.append( os.environ['AFQMCLAB_DIR']+"/scripts/fit" )
from fitPolynomial import *

x,y=np.loadtxt("data", unpack=True)
popt,perr=fit(2, x, y)
fit_plot(popt, x, y)