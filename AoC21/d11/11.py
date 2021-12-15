from itertools import *
from functools import *
from collections import *
import re

arr = []
for l in open("i1"):
    l = l.strip()
    arr.append([int(x) for x in l])


dx = [-1,0,1]
dy = [-1,0,1]
r = len(arr)
c = len(arr[0])
res = 0
turn = 1
while True:
    for i in range(r):
        for j in range(c):
            arr[i][j] = arr[i][j]+1
        
    flash = True 
    while flash:
        flash = False
        for i in range(r):
            for j in range(c):
                if arr[i][j] > 9:
                    flash = True
                    arr[i][j] = 0
                    for x in dx:
                        for y in dy:
                            if x == y == 0:
                                continue
                            X = x+i
                            Y = y+j
                            if 0 <= X < r and 0 <= Y < c:
                                arr[X][Y] += 1 if arr[X][Y] > 0 else 0
    #Part1
    for x in arr:
        res += x.count(0)
    if turn == 100:
        print(res)
    #part2
    ok = True
    for x in arr:
        for y in x:
            if y != 0:
                ok = False
    if ok:
        print(turn)
        exit()
    turn += 1
    
print(res)
