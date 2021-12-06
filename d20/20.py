from copy import deepcopy
from itertools import * 
import re
import math

def rot_flip(m):
    #rotation
    m1 = [[c[i] for c in m] for i in range(len(m))[::-1]]
    m2 = [[c[i] for c in m1] for i in range(len(m1))[::-1]]
    m3 = [[c[i] for c in m2] for i in range(len(m2))[::-1]]
    #flips
    m4 = m[::-1]
    m5 = m1[::-1]
    m6 = m2[::-1]
    m7 = m3[::-1]
    return [m,m1,m2,m3,m4,m5,m6,m7]

arr = {} 
temp = []
for i in open("i1"):
    i = i.strip()
    if not i:
        arr[tile] = temp 
        continue
    elif re.search("\d",i):
        temp = []
        tile = re.findall("\d+",i)[0]
        continue
    else:
        temp.append(list(i))

arr[tile] = temp
n = int(math.sqrt(len(arr))) 
nn = len(temp)
#Backtracking
def bt(mat,used,i,j,pairs):
    nm = deepcopy(mat)
    p = deepcopy(pairs)
    u = used.copy()
    if i == n and j == 0:
        return (pairs,mat)
    for k in arr.keys():
        if k not in used:
            comb = rot_flip(arr[k])
            for c in comb:
                match = True
                for l in range(nn):
                    if i > 0:
                        if nm[i-1][j][nn-1][l] != c[0][l]:
                            match = False
                    if j > 0:
                        if nm[i][j-1][l][nn-1] != c[l][0]:
                            match = False
                if match:
                    nm[i][j] = c
                    p[(i,j)] = k 
                    u.add(k)
                    if j == n-1:
                        return bt(nm, u, i+1,0, p)
                    else:
                        return bt(nm, u, i, j+1, p)
#part1
for x in arr.keys():
    res = [[None]*n for x in range(n)]
    res[0][0] = arr[x]
    s = set()
    s.add(x)
    ret = bt(res,s,0,1,{(0,0):x}) 
    if ret:
        ret,mat = ret
        s = int(ret[(0,0)])*int(ret[(n-1,0)])*int(ret[(0,n-1)])*int(ret[(n-1,n-1)])
        print(s)
        break
