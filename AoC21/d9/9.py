from collections import deque 
arr = []
for l in open("i1"):
    arr.append([int(x) for x in l.strip()])


R = len(arr)
C = len(arr[0])

pairs = [(1,0),(-1,0),(0,-1),(0,1)]

#part 1, just find every point which has bigger neighbours
res = []
basins = []
for x in range(R):
    for y in range(C):
        ok = True
        for dx,dy in pairs:
            X = dx+x
            Y = dy+y
            if 0<=X<R and 0<=Y<R:
                if arr[x][y] >= arr[X][Y]:
                    ok = False
        if ok:
            basins.append((x,y))
            res.append(arr[x][y])

print(sum(res)+len(res))

# For every point found in part 1
# Expand the area until edge or wall of nines
# count the number of tiles that are expanded including start
seen = set()
res = []
for x,y in basins:
    q = deque()
    q.append((x,y))
    found = 0
    while q:
        (x,y) = q.popleft()
        if (x,y) in seen:
            continue
        seen.add((x,y))
        found += 1
        for dx,dy in pairs:
            X = dx+x
            Y = dy+y
            if 0<=X<R and 0<=Y<C and arr[X][Y] != 9:
                q.append((X,Y))
    res.append(found)

a,b,c = sorted(res)[-3::]
print(a*b*c)
