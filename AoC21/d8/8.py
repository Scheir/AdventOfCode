import re
from collections import *
from functools import *

inp = []
arr = []

for l in open("i1"):
    l = l.strip()
    a,b = l.split("|")
    arr.append(b.split())
    inp.append(a.split())
res = 0
for x in arr:
    for y in x:
        if len(y) in (2,3,4,7):
            res += 1

print(res)
res = 0
for i, x in enumerate(arr):
    y = inp[i]
    d = {}
    for w in sorted(y, key=len):
        word = set(w)
        size = len(w)
        if size == 2:
            d[1] = word
        elif size == 3:
            d[7] = word
        elif size == 4:
            d[4] = word
        elif size == 7:
            d[8] = word
        elif size == 5:
            if len(word & d[7]) == 3:
                d[3] = word
            elif len(word & d[4]) == 3:
                d[5] = word
            else:
                d[2] = word
        elif size == 6:
            if len(word & d[5]) == 5:
                if len(word & d[7]) == 2:
                    d[6] = word
                else:
                    d[9] = word
            else:
                d[0] = word

    string = ''.join([str(k) for ele in x for k in d.keys() if d[k] == set(ele)])
    res += int(string)

print(res)
