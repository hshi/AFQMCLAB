import os
import numpy as np
import sys; sys.path.append( os.environ['AFQMCLAB_DIR']+"/scripts/fit" )
import linear

x,y=np.loadtxt("data", unpack=True)
popt,perr=linear.fit(x, y)
linear.plot(popt, x, y, xmin=0.0)