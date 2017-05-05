#Program: Chi-Square fitting to a straight line
#NOTICE: fit y=a+bx with or without error bar of y.
#Give out a and b with error bars, no output goodness-of-fit.

#REFERENCE:
#For y with no error bar: http://mathworld.wolfram.com/LeastSquaresFitting.html
#For y with error bar: NUMERICAL RECIPES IN FORTRAIN II P656

import numpy as np
import matplotlib.pyplot as plt

def fitWithOutErrorBar(x, y):
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

    return a,b,da,db

def fitWithErrorBar(x, y, dy):
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

    return a,b,da,db

def fit(x, y, dy = None):
    if dy is None:
        a,b,da,db = fitWithOutErrorBar(x, y)
    else:
        a,b,da,db = fitWithErrorBar(x, y, dy)

    print ( "parameters:", a   , b )
    print ( "param err :", da  , db )
    print ( "relative  :", da/a, db/b )

    if dy is not None:
        fit_y=a+x*b
        chi=np.sum( (fit_y-y)**2/dy**2 )
        print ( "Chi-sqaure with data lenth:", chi, len(x) )

    return np.array([a,b]),np.array([da,db])

def plot(popt, x, y, dy=None, xmin=None, xmax=None, save=0):
    fig, ax = plt.subplots()
    ax.set_xlabel('$x$')
    ax.set_xlabel('$y$')

    if dy is None:
        ax.plot(x, y,'bo',label='data')
    else:
        ax.errorbar(x, y, yerr=dy,fmt='bo',label='data')

    if xmin==None:
       xmin=np.amin(x)
    if xmax==None:
       xmax=np.amax(x)

    fitx =np.linspace(xmin,xmax,512,endpoint=True)
    fity =popt[0]+fitx*popt[1]
    ax.plot(fitx, fity,'r-',label='fit curve')

    ax.legend(loc='upper right',frameon=False)

    if save==0:
        plt.show()
    else:
        fig.savefig('fit.pdf',bbox_inches='tight')