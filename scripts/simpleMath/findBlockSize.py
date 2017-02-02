import numpy as np
import math

def factor(n):
    factors = set()
    for x in range(1, int(math.sqrt(n)) + 1):
      if n % x == 0:
        factors.add(x)
        factors.add(n//x)
    return sorted(factors)

def findBlockSize(n):
    if n==0:
       return 1;
    factors = np.array( factor(n) )
    factor_sum = ( factors + n/factors ).tolist();
    index = factor_sum.index(min(factor_sum))
    return factors[index]