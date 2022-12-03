from collections import *
def res(d):
    ret = 0
    for k,v in d.items():
        if k.islower():
            ret += (ord(k)-ord('a')+1)*v
        else:
            ret += (ord(k)-ord('A')+27)*v
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
