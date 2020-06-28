import math
from decimal import *

def fac(n):
    i = n
    out = 1
    while(i > 0):
        out = out * i
        i -= 1
    return out
      
k = 0
radical_mess = 426880 * math.sqrt(10005)
divider_mess = Decimal("0.0")
getcontext().prec = 10000
out = 0
while(k < 100000):
    denominator = Decimal(fac(6 * k) * ((545140134 * k) + 13591409))
    numerator = Decimal(fac(3 * k) * (fac(k) ** 3) * (-262537412640768000 ** k))
    divider_mess += denominator / numerator
    out = Decimal(radical_mess) / divider_mess
    print(out)
    k += 1

