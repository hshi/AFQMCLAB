import numpy as np
import sys; sys.path.append("/home/boruoshihao/fit/python") # Path about the fit src code
from fit_linear import *

x,y=np.loadtxt("data", dtype=np.float64,skiprows=0,unpack=True)
popt,perr=fit(x, y)
fit_plot(x, y, popt, xmin="none", xmax="none", save=1)
