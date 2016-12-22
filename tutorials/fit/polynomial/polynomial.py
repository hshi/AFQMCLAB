import numpy as np
import sys; sys.path.append("/home/boruoshihao/fit/python") # Path about the fit src code
from fit import *

def fun(x,a,b):
    return a+b*x**2
p0=[-9.213378324437171, -634.2556002942869]

x,y,dy=np.loadtxt("data", dtype=np.float64,skiprows=0,unpack=True)
popt,perr=fit(fun, x, y, dy, p0)
fit_plot(fun, x, y, dy, popt, xmin="none", xmax="none", save=0)
