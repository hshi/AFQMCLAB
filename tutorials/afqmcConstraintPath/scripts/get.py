import numpy as np

h = np.loadtxt("HNum.dat")
k = np.loadtxt("KNum.dat")
v = np.loadtxt("VNum.dat")
d = np.loadtxt("den.dat")

np.savetxt("h.dat", (h[:,0] / d[:, 0]))
np.savetxt("k.dat", (k[:,0] / d[:, 0]))
np.savetxt("v.dat", (v[:,0] / d[:, 0]))
