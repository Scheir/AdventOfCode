import heapq

m = []
for i in open("i1"):
    i = i.strip()
    m.append([int(x) for x in list(i)])

cur = (0,0,0)
q = []
R = len(m)
C = len(m[0])
heapq.heappush(q,cur)
visited = [[0]*R for _ in range(C)]

while len(q):
    cnt,x,y = heapq.heappop(q)
    if (x,y) == (C-1,R-1):
        print(cnt)
        exit()

    for i,j in ((-1,0),(1,0),(0,-1),(0,1)):
        X = x+i
        Y = y+j
        if 0<=X<R and 0<=Y<C and visited[X][Y] == 0:
            visited[X][Y] = -1
            heapq.heappush(q,(cnt+m[X][Y],X,Y))



