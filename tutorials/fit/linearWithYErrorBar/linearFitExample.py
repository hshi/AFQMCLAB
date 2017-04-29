import os
import numpy as np
import sys; sys.path.append( os.environ['AFQMCLAB_DIR']+"/scripts/fit" )
from fitLinear import *

x,y,dy=np.loadtxt("data", unpack=True)
popt,perr=fit(x, y, dy)
fit_plot(popt, x, y, dy, xmin=0.0)