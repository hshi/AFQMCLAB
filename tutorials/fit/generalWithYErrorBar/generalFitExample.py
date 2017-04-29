import os
import numpy as np
import sys; sys.path.append( os.environ['AFQMCLAB_DIR']+"/scripts/fit" )
from fitGeneral import *

def fun(x,a,b,c):
    return a + b*x**2 + np.exp(c*x)

p0=[0.0, 1.0, 2.0]

x,y,dy=np.loadtxt("data", unpack=True)

popt,perr=fit(fun, x, y, dy, p0)

fit_plot(fun, popt, x, y, dy)