from itertools import *
from collections import defaultdict
arr = []
with open("i1") as file:
    for l in file:
        arr.append(int(l.rstrip()))

total_liters = 150
count = 0
d = defaultdict(int) 
for i in range(1,len(arr)+1):
    for x in combinations(arr, i):
        if sum(x) == total_liters:
            count += 1
            d[len(x)] += 1
            
print(count)
print(d[min(d.keys())])
