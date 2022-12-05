from copy import deepcopy
from itertools import *
import re

arr = []
ins = []
b = False
for row in open("i1"):
    if row == "\n":
        b = True
    else:
        if not b:
            arr.append(row)
        else:
            ins.append(row.strip())

# Transpose
arr = list(map(list,zip(*arr)))

mat = []
temp = []
# Find all letters, when we reach a number append and continue
for x in chain(*arr):
    if x.isnumeric():
        mat.append(temp[::-1])
        temp.clear()
    elif x.isalpha():
        temp.append(x)


mat2 = deepcopy(mat) 

#p1
for i in ins:
    a,b,c = [int(x) for x in re.findall("\d+", i)]
    for j in range(a):
        mat[c-1].append(mat[b-1].pop())

print(''.join(x[-1] for x in mat))

#P2
for i in ins:
    a,b,c = [int(x) for x in re.findall("\d+", i)]
    l = []
    for j in range(a):
        l = [mat2[b-1].pop()] + l 
    mat2[c-1] += l

print(''.join(x[-1] for x in mat2))
