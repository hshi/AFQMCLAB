import numpy as np
from scipy.optimize import curve_fit
import pylab

def fit(func, x, y, dy, p0='none'):
    data_len = len(x)
    if p0=='none':
       popt, pcov = curve_fit(func, x, y, sigma=dy)
    else:
       popt, pcov = curve_fit(func, x, y, p0, dy)
    perr = np.sqrt(np.diag(pcov))


    print ( "parameters:", popt.tolist() )
    print ( "param err :", perr.tolist() )
    print ( "relative  :", (perr/popt).tolist() )

    fun_y=func(x, *popt)
    chi=np.sum( (fun_y-y)**2/dy**2 )
    print ( "Chi-sqaure with data lenth:", chi, data_len )

    return popt,perr


def fit_plot(func, x, y, dy, popt, xmin="none", xmax="none", save=0):
    pylab.figure()
    pylab.xlabel('$x$')
    pylab.ylabel('$y$')
    pylab.errorbar(x, y, yerr=dy,fmt='bo',label='data')

    if xmin=="none":
       xmin=np.amin(x)
    if xmax=="none":
       xmax=np.amax(x)
    fitx =np.linspace(xmin,xmax,512,endpoint=True)
    fity =func(fitx, *popt)
    pylab.plot(fitx, fity,'r-',label='fit curve')

    pylab.legend(loc='upper right',frameon=False)

    if save==0:
       pylab.show()
    else:
       pylab.savefig('fit.pdf',bbox_inches='tight')
