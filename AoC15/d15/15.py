import re
from functools import reduce
arr = []
with open("i2") as file:
    for l in file:
        arr.append(re.findall("-?\d+", l))

mat = []
for x in range(len(arr[0])):
    mat.append([int(r[x]) for r in arr])

winner = 0
winner2 = 0
for i in range(0, 101):
    for j in range(0, 101-i):
        for k in range(0,101-i-j):
            l = 100-i-j-k
            a,b,c,d,e = [max(sum(map(lambda xx, yy: int(xx)*yy, r, [i,j,k,l])), 0) for r in mat]
            prod = a*b*c*d
            winner = prod if prod > winner else winner
            if e == 500:
                winner2 = prod if prod > winner2 else winner2

print(winner)
print(winner2)
