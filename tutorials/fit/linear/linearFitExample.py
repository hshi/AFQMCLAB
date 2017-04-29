import os
import numpy as np
import sys; sys.path.append( os.environ['AFQMCLAB_DIR']+"/scripts/fit" )
from fitLinear import *

x,y=np.loadtxt("data", unpack=True)
popt,perr=fit(x, y)
fit_plot(popt, x, y, xmin=0.0)