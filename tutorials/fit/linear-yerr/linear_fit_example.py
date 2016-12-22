import os
import numpy as np
import sys; sys.path.append( os.environ['AFQMC_DIR']+"/scripts/fit" )
from fit_linear_yerr import *

x,y,dy=np.loadtxt("data", dtype=np.float64,skiprows=0,unpack=True)
popt,perr=fit(x, y, dy)
fit_plot(x, y, dy, popt, xmin="none", xmax="none", save=0)
