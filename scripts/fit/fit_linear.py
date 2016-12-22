#Program: Chi-Square fitting to a straight line
#NOTICE: fit y=a+bx.
#Give out a and b with error bars, no output goodness-of-fit.
#REFERENCE http://mathworld.wolfram.com/LeastSquaresFitting.html

import numpy as np
import pylab

def fit(x, y):
    data_len = np.float64( len(x) )

    xmean = x.mean()
    ymean = y.mean()
    Sxx   = (x*x).sum()-xmean*xmean*data_len
    Syy   = (y*y).sum()-ymean*ymean*data_len
    Sxy   = (x*y).sum()-xmean*ymean*data_len
    S     = np.sqrt( (Syy-Sxy*Sxy/Sxx)/(data_len-2.0) )

    b=Sxy/Sxx
    a=ymean-b*xmean
    da=S*np.sqrt( 1.0/data_len + xmean*xmean/Sxx )
    db=S/np.sqrt( Sxx )

    print ( "parameters:", a   , b )
    print ( "param err :", da  , db )
    print ( "relative  :", da/a, db/b )

    return np.array([a,b]),np.array([da,db])

def fit_plot(x, y, popt, xmin="none", xmax="none", save=0):
    pylab.figure()
    pylab.xlabel('$x$')
    pylab.ylabel('$y$')
    pylab.plot(x, y,'bo',label='data')

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

