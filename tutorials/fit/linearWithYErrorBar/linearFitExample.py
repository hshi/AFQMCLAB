import os
import numpy as np
import sys; sys.path.append( os.environ['AFQMCLAB_DIR']+"/scripts/fit" )
import linear

x,y,dy=np.loadtxt("data", unpack=True)
popt,perr=linear.fit(x, y, dy)
linear.plot(popt, x, y, dy, xmin=0.0)