from collections import defaultdict
from copy import deepcopy
arr = []
for i in open("i1"):
    arr.append(i.strip())

hexa = [[0]*200 for x in range(200)]
for line in arr:
    i = 0
    x,y = 100,100
    while i < len(line):
        if line[i] == "s":
            if line[i+1] == "w":
                y-=1
            else:
                x+=1
                y-=1
            i+=2
        elif line[i] == "n":
            if line[i+1] == "w":
                x-=1
                y+=1
            else:
                y+=1
            i+=2
        elif line[i] == "w":
            x-=1
            i+=1
        else:
            x+=1
            i+=1
    hexa[x][y] += 1

res = 0
for x in hexa:
    for y in x:
        if y%2 != 0:
            res += 1
print(res)
pairs = ((0,1),(1,0),(1,-1),(0,-1),(-1,0),(-1,1))

for _ in range(100):
    th = deepcopy(hexa)
    for i in range(1,199):
        for j in range(1,199):
            cnt = 0
            for dx,dy in pairs:
                x = dx+i
                y = dy+j
                if th[x][y] % 2 != 0:
                    cnt += 1
            if th[i][j] % 2 != 0:
                if cnt == 0 or cnt > 2:
                    hexa[i][j] += 1
            else:
                if cnt == 2:
                    hexa[i][j] += 1
    res = 0
    for a in hexa:
        for b in a:
            if b % 2 != 0:
                res+=1
    print(_+1,res)

    

    
