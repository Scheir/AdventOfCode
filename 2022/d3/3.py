from collections import *
from string import ascii_lowercase as LOWER
from string import ascii_uppercase as UPPER

def res(d):
    ret = 0
    for k,v in d.items():
        if k in LOWER:
            ret += (LOWER.index(k)+1)*v
        else:
            ret += (UPPER.index(k)+27)*v
    return ret


arr = []
for row in open("i1"):
    arr.append(row.strip())    


d = defaultdict(int)
for row in arr:
    a = set(row[:len(row)//2])
    b = set(row[len(row)//2:])
    dup = list((a&b))[0]
    d[dup] += 1

print(res(d))

d.clear()
for i in range(0,len(arr),3):
    a,b,c = [set(x) for x in arr[i:i+3]]
    dup = list(a&b&c)[0]
    d[dup] += 1

print(res(d))
