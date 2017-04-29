import numpy as np
from scipy.optimize import curve_fit
import matplotlib.pyplot as plt

def fit(func, x, y, dy=None, p0=None):
    popt, pcov = curve_fit(func, x, y, p0, dy)
    perr = np.sqrt(np.diag(pcov))

    print ( "parameters:", popt.tolist() )
    print ( "param err :", perr.tolist() )
    print ( "relative  :", (perr/popt).tolist() )

    if dy is not None:
        fun_y=func(x, *popt)
        chi=np.sum( (fun_y-y)**2/dy**2 )
        print ( "Chi-sqaure with data lenth:", chi, len(x) )

    return popt,perr

def fit_plot(func, popt, x, y, dy=None, xmin=None, xmax=None, save=0):
    fig, ax = plt.subplots()
    ax.set_xlabel('$x$')
    ax.set_xlabel('$y$')

    if dy is None:
        ax.plot(x, y,'bo',label='data')
    else:
        ax.errorbar(x, y, yerr=dy,fmt='bo',label='data')

    if xmin is None:
        xmin=np.amin(x)
    if xmax is None:
        xmax=np.amax(x)

    fitx =np.linspace(xmin,xmax,512,endpoint=True)
    fity =func(fitx, *popt)

    ax.plot(fitx, fity,'r-',label='fit curve')

    ax.legend(loc='upper right',frameon=False)

    if save==0:
        plt.show()
    else:
        fig.savefig('fit.pdf',bbox_inches='tight')