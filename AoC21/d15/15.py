import heapq
def dijkstra(mat):
    R = len(mat)
    C = len(mat[0])
    visited = [[0] * C for _ in range(R)]
    q = [] 
    current = (0,0,0)
    heapq.heappush(q,current)
    while len(q):
        cnt,x,y = heapq.heappop(q)
        if (x,y) == (C-1,R-1):
            return cnt
        for i,j in ((-1,0),(1,0),(0,-1),(0,1)):
            X = x+i
            Y = y+j
            if 0<=X<R and 0<=Y<C and visited[X][Y] == 0:
                visited[X][Y] = -1
                heapq.heappush(q,(cnt+mat[X][Y],X,Y))
t = []
for i in open("i1"):
    i = i.strip()
    t.append([int(x) for x in list(i)])

print(dijkstra(t))
mat = [[0]*len(t)*5 for x in range(len(t[0])*5)]
for _ in range(5):
    for __ in range(5):
        for x in range(len(t)):
            for y in range(len(t[0])):
                v = t[x][y] + _  +__ 
                v = v-9 if v > 9 else v
                mat[x+_*len(t)][y+__*len(t[0])] = v

t = mat
print(dijkstra(t))
