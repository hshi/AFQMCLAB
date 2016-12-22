#Program: Chi-Square fitting to a straight line
#NOTICE: fit y=a+bx with error bar of y. Give out
#a and b with error bars, no output goodness-of-fit.
#REFERENCE: NUMERICAL RECIPES IN FORTRAIN II P656

import numpy as np
import pylab

def fit(x, y, dy):
    data_len = len(x)

    inv_y2 = 1.0/(dy*dy)
    S      = inv_y2.sum()
    Sx     = (x*inv_y2).sum()
    Sy     = (y*inv_y2).sum()
    Sxx    = (x*x*inv_y2).sum()
    Sxy    = (x*y*inv_y2).sum()
    delta  = S*Sxx-Sx*Sx

    a=(Sxx*Sy-Sx*Sxy)/delta
    b=(S*Sxy-Sx*Sy)/delta
    da=np.sqrt(Sxx/delta)
    db=np.sqrt(S/delta)

    print ( "parameters:", a   , b )
    print ( "param err :", da  , db )
    print ( "relative  :", da/a, db/b )

    fit_y=a+x*b
    chi=np.sum( (fit_y-y)**2/dy**2 )
    print ( "Chi-sqaure with data lenth:", chi, data_len )

    return np.array([a,b]),np.array([da,db])

def fit_plot(x, y, dy, popt, xmin="none", xmax="none", save=0):
    pylab.figure()
    pylab.xlabel('$x$')
    pylab.ylabel('$y$')
    pylab.errorbar(x, y, yerr=dy,fmt='bo',label='data')

    if xmin=="none":
       xmin=np.amin(x)
    if xmax=="none":
       xmax=np.amax(x)
    fitx =np.linspace(xmin,xmax,512,endpoint=True)
    fity =popt[0]+fitx*popt[1]
    pylab.plot(fitx, fity,'r-',label='fit curve')

    pylab.legend(loc='upper right',frameon=False)

    if save==0:
       pylab.show()
    else:
       pylab.savefig('fit.pdf',bbox_inches='tight')

