import re
import math
from collections import *
from functools import *

arr = []
for i in open("i1"):
    arr = i.strip().split(",")

i.strip().split(",")
res = 10e10
res2 = 10e10
for x in range(1000):
    tr = 0
    tr2 = 0
    for y in arr:
        y = int(y)
        r = abs(x-y)
        tr += r*(1+r)/2 
        tr2 += r 
    res2 = res2 if res2 < tr2 else tr2 
    res = res if res < tr else tr

print(res2)
print(int(res))
