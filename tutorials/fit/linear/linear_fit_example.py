import os
import numpy as np
import sys; sys.path.append( os.environ['AFQMCLAB_DIR']+"/scripts/fit" )
from fit_linear import *

x,y=np.loadtxt("data", dtype=np.float64,skiprows=0,unpack=True)
popt,perr=fit(x, y)
fit_plot(x, y, popt, xmin="none", xmax="none", save=0)
