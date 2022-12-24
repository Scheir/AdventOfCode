from heapq import *
from collections import defaultdict
from copy import deepcopy
arr = []
for x in open("i1"):
    arr.append(([r for r in x.strip()]))


R,C = len(arr),len(arr[0])
start = next((i for i ,x in enumerate(arr[0]) if x != "#"))


B = defaultdict(str)
for i,row in enumerate(arr):
    for j,x in enumerate(row):
        if x not in "#.":
            B[(i,j)] += x


MAPS = {0:B}
for _ in range(0,2000):
    ret = defaultdict(str)
    for (x,y),v in B.items():
        if ">" in v: 
            if y == C-2:
                ret[(x,1)] += ">"
            else:
                ret[(x,y+1)]+= ">"

        if "<" in v:
            if y == 1:
                ret[(x,C-2)] += "<"
            else:
                ret[(x,y-1)]+= "<"

        if "^" in v: 
            if x == 1:
                ret[(R-2,y)] += "^"
            else:
                ret[(x-1,y)] += "^"

        if "v" in v:
            if x == R-2:
                ret[(1,y)] += "v"
            else:
                ret[(x+1,y)] += "v"
    B = ret
    MAPS[_] = B


R = len(arr)
C = len(arr[0])
q = [(0,0,start)]
DIR = ((0,0),(1,0),(0,1),(-1,0),(0,-1))
seen = set()
done = False
GOAL = (R-1,C-2)
while q:
    if done:
        break
    c,x,y = heappop(q)
    if (c,x,y) in seen:
        continue
    seen.add((c,x,y))
    
    CUR_MAP = MAPS.get(c)
    for dx,dy in DIR:
        X = x+dx
        Y = y+dy
        if (X,Y) == GOAL:
            print(c+1)
            done = True
        if (X,Y) == (0,start) or (1<=X<R-1 and 1<=Y<C-1):
            if (X,Y) not in CUR_MAP: 
                heappush(q,(c+1,X,Y))


#part2
q = [(0,0,start,False,False)]
seen = set()
while q:
    c,x,y,found_end,went_back = heappop(q)
    print(c,x,y)
    if (c,x,y,found_end,went_back) in seen:
        continue
    seen.add((c,x,y,found_end,went_back))
    
    CUR_MAP = MAPS.get(c)
    for dx,dy in DIR:
        X = x+dx
        Y = y+dy
        if X == R-1 and Y == C-2:
            if went_back:
                print(c+1)
                exit()
            heappush(q,(c+1,X,Y,True,False))
        elif (X,Y) == (0,start) and found_end:
            heappush(q,(c+1,X,Y,True,True))
        elif (X,Y) == (0,start) or (1<=X<R-1 and 1<=Y<C-1):
            if (X,Y) not in CUR_MAP: 
                heappush(q,(c+1,X,Y,found_end,went_back))
