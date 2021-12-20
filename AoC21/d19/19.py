from functools import *
from itertools import *
import re
from collections import *

beacs = []
f = open("i1").read().split("\n\n")

for x in f:
    x = x.strip().split("\n")
    ta = []
    for pos in x[1:]:
        ta.append([int(cord) for cord in pos.split(",")])
    beacs.append(ta)

directions = [(1,1,1),(1,1,-1),(1,-1,1),(1,-1,-1),(-1,1,1),(-1,1,-1),(-1,-1,1),(-1,-1,-1)]
perms = list(permutations((0,1,2)))
adj_b = {}
for i in range(len(beacs)):
    idx = 0
    for d1,d2,d3 in directions:
        for p1,p2,p3 in perms:
            adj_b[(i,idx)] = [[x[p1]*d1,x[p2]*d2,x[p3]*d3] for x in beacs[i]]        
            idx += 1

FOUND = set([tuple(x) for x in beacs[0]])
POS = {}
POS[0] = (0,0,0)
def solve():
    for i in range(len(beacs)):
        if i in POS:
            continue
        ok = False
        cands = defaultdict(int)
        for idx in range(48):
            for cords in adj_b[(i,idx)]:
                for m_cords in FOUND: 
                    dx = -cords[0]+m_cords[0]
                    dy = -cords[1]+m_cords[1]
                    dz = -cords[2]+m_cords[2]
                    cands[(dx,dy,dz)] += 1
                for xyz,val in cands.items():
                    if val >= 12:
                        print("Scanner found at: ",xyz)
                        for x,y,z in adj_b[(i,idx)]:
                            FOUND.add((x+xyz[0], y+xyz[1], z+xyz[2]))
                        POS[i] = (xyz[0],xyz[1],xyz[2])
                        return

while len(POS) != len(beacs):
    solve()
print(len(FOUND))

res = 0
for x in POS.values():
    for y in POS.values():
        d = abs(x[0]-y[0]) + abs(x[1]-y[1]) + abs(x[2]-y[2])
        res = max(res,d)
print(res)
