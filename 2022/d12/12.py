from heapq import *

def dijkstra(arr,goal,p2=False):
    DIR = ((0,1),(1,0),(-1,0),(0,-1))
    q = []
    for i,row in enumerate(arr):
        for j,x in enumerate(row):
            if p2:
                if x == 1:
                    q.append((0,i,j))
            else:
                if x == 0:
                    q.append((0,i,j))

    R,C = len(arr),len(arr[0])
    seen = set()
    while q:
        c,x,y = heappop(q)
        if (x,y) == goal:
            return c
        if (x,y) in seen:
            continue
        seen.add((x,y))
        for dx,dy in DIR:
            X = x+dx
            Y = y+dy
            if 0<=X<R and 0<=Y<C:
                if arr[X][Y] <= arr[x][y]+1:
                    heappush(q,(c+1,X,Y))

arr = []
for row in open("i1"):
    arr.append([x for x in row.strip()])
for i,row in enumerate(arr):
    for j,x in enumerate(row):
        if x == "S":
            arr[i][j] = 0
        elif x == "E":
            goal = (i,j)
            arr[i][j] = 26 
        else:
            arr[i][j] = ord(x)-ord('a')+1

print(dijkstra(arr,goal))
print(dijkstra(arr,goal,True))
