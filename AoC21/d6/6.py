import re
from collections import *
from functools import *


arrr = [] 
for i in open("i1"):
    arrr = i.strip().split(',')
    arrr = [int(x) for x in arrr]

arr = defaultdict(int)
for x in arrr:
    arr[x] += 1

for _ in range(256):
    if _ == 80:
        res = sum([arr[x] for x in arr])
        print(res)
    zos = 0
    for i in range(8):
        if i == 0:
           zos += arr[0] 
        arr[i] = arr[i+1]
    arr[8] = zos
    arr[6] += zos

res = sum([arr[x] for x in arr])
print(res)
