from collections import deque
import re
arr = []
with open("i1") as file:
    for l in file:
        arr.append(l.rstrip().split())

mat = [['.'] * 50 for x in range(6)]

for x in arr:
    if x[0] == "rect":
        a,b = x[1].split('x')
        a,b = int(a), int(b)
        for i in range(b):
            mat[i][:a] = ['#']*a
    else:
        a,b = re.findall("\d+", ''.join(x[2:]))
        a = int(a)
        b = int(b)
        if x[1] == "column":
            mat = list(map(list,zip(*mat)))
        de = deque(mat[a])
        de.rotate(b)
        mat[a] = list(de)
        if x[1] == "column":
            mat = list(map(list,zip(*mat)))
            
res = 0
for x in mat:
    res += x.count('#')
    print(x)
print(res)
