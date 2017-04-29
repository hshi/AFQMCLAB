#Note!!!!!
#The variance estimation of each coefficient is from diagonal part of covariance matrix,
#Which is not consistent with fitLinear.py when polynomial is 2.
#I Checked the fitLinear.py at http://mathworld.wolfram.com/LeastSquaresFitting.html and
#NUMERICAL RECIPES IN FORTRAIN II P656, did not find any bug.
#Maybe the variance estimation is different for general polynomial function and linear function.
#Recommend to use fitLinear.py for linear function.

import numpy as np
import matplotlib.pyplot as plt

def fit(n, x, y, dy=None):
    if dy is None:
        popt, pcov = np.polyfit(x, y, n, full=False, cov=True)
    else:
        popt, pcov = np.polyfit(x, y, n, full=False, w=1/dy, cov=True)
    perr = np.sqrt(np.diag(pcov))

    #popt and perr is ordered from high to low, use [::-1] to reverse the print order
    print ( "parameters:", popt[::-1].tolist() )
    print ( "param err :", perr[::-1].tolist() )
    print ( "relative  :", (perr/popt)[::-1].tolist() )

    if dy is not None:
        func = np.poly1d(popt)
        fun_y=func(x)
        chi=np.sum( (fun_y-y)**2/dy**2 )
        print ( "Chi-sqaure with data lenth:", chi, len(x) )

    return popt,perr

def fit_plot(popt, x, y, dy=None, xmin=None, xmax=None, save=0):
    fig, ax = plt.subplots()
    ax.set_xlabel('$x$')
    ax.set_xlabel('$y$')

    if dy is None:
       ax.plot(x, y,'bo',label='data')
    else:
       ax.errorbar(x, y, yerr=dy,fmt='bo',label='data')

    func = np.poly1d(popt)

    if xmin is None:
        xmin=np.amin(x)
    if xmax is None:
        xmax=np.amax(x)

    print

    fitx =np.linspace(xmin,xmax,512,endpoint=True)
    fity = func( fitx )

    ax.plot(fitx, fity,'r-',label='fit curve')

    ax.legend(loc='upper right',frameon=False)

    if save==0:
        plt.show()
    else:
        fig.savefig('fit.pdf',bbox_inches='tight')