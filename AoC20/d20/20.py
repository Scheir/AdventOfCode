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

#Backtracking algorithm, starting with a set image at cord 0,0 and 
#trying to find a solution
#Returning the big matrix and pair with ID's coordinates
def bt(mat,used,i,j,pairs):
    nm = deepcopy(mat)
    p = deepcopy(pairs)
    u = used.copy()
    if i == n and j == 0:
        return (pairs,nm)
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
                        ret = bt(nm, u, i+1,0, p)
                    else:
                        ret = bt(nm, u, i, j+1, p)
                    # If ret is not false, then it means that we found a solution
                    # and ret pairs and the final matrix, return it and we are done!
                    if ret:
                        return ret
    return False

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

#part1
#Try for each smaller picture as the fixed 0,0 part
#until we find a solution
for x in arr.keys():
    res = [[None]*n for x in range(n)]
    res[0][0] = arr[x]
    s = set()
    s.add(x)
    ret = bt(res,s,0,1,{(0,0):x}) 
    if ret:
        #Ret is the pair (ID,(x,y))
        #Mat is the final picture
        ret,mat = ret
        s = int(ret[(0,0)])*int(ret[(n-1,0)])*int(ret[(0,n-1)])*int(ret[(n-1,n-1)])
        print(s)
        break

#Create the image, remove borders of each image part
newmat = []
for l in range(n):
    tvv = deepcopy(mat[l][0])
    for a,b in enumerate(tvv):
        tvv[a] = b[1:-1]
    tvv = tvv[1:-1]
    for j in range(1,n):
        for i,x in enumerate(mat[l][j][1:-1]):
            tvv[i] = tvv[i]+x[1:-1]
    for x in tvv:
        newmat.append(x)


#Monster arrays to match
m1 = list("                  # ")
m2 = list("#    ##    ##    ###")
m3 = list(" #  #  #  #  #  #   ")

#Try all combinations to see which one has the monsters
comb = rot_flip(newmat)
res = 0
for co in comb:
    tr = 0
    for i in range(len(co)-3):
        a,b,c = co[i:i+3]
        for y in range(len(co[0])-len(m1)):
            ok = True 
            aa,bb,cc = a[y:y+len(m1)],b[y:y+len(m2)], c[y:y+len(m2)]
            for z,x in enumerate(aa):
                if  m1[z] == "#" and x == '.':
                    ok = False
                    break
            for z,x in enumerate(bb):
                if m2[z] == "#" and x == '.':
                    ok = False
                    break
            for z,x in enumerate(cc):
                if m3[z] == "#" and x == '.':
                    ok = False
                    break
            if ok: 
                tr += m1.count("#") + m2.count("#") + m3.count("#")
    res = res if res > tr else tr

hashes = sum([x.count("#") for x in newmat])  
print(hashes-res)
