import re
from collections import *
from functools import *


arr = []
for i in open("i1"):
    i = i.rstrip()
    a,b,c,d = re.findall("\d+",i)
    arr.append((int(a),int(b),int(c),int(d)))


dd = {} 
for a,b,c,d in arr:
    if a == c:
        i = max(b,d)
        j = min(b,d)
        for x in range(j,i+1):
            if (a,x) not in dd:
                dd[(a,x)] = 1
            else:
                dd[(a,x)] += 1
    if b == d:
        i = max(a,c)
        j = min(a,c)
        for x in range(j,i+1):
            if (x,b) not in dd:
                dd[(x,b)] = 1
            else: 
                dd[(x,b)] += 1
    else:
        if a > c and b > d:
            print("1")
            for x,_ in enumerate(range(c,a+1)):
                if(a-x, b-x) not in dd:
                    dd[(a-x,b-x)] = 1
                else:
                    dd[(a-x, b-x)] += 1
        elif a > c and b < d:
            print("2")
            print(a,b,c,d)
            for x,_ in enumerate(range(c,a+1)):
                if(a-x, b+x) not in dd:
                    dd[(a-x,b+x)] = 1
                else:
                    dd[(a-x, b+x)] += 1
        
        elif a < c and b < d:
            print("3")
            for x,_ in enumerate(range(a,c+1)):
                if(a+x, b+x) not in dd:
                    dd[(a+x,b+x)] = 1
                else:
                    dd[(a+x, b+x)] += 1
        elif a < c and b > d:
            print("4")
            print(a,b,c,d)
            for x,_ in enumerate(range(a,c+1)):
                if(a+x, b-x) not in dd:
                    dd[(a+x,b-x)] = 1
                else:
                    dd[(a+x,b-x)] += 1

res = 0
for x in dd:
    if dd[x] >= 2:
        print(x, dd[x])
        res += 1

print(res)
        



