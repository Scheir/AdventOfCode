from collections import defaultdict
from itertools import cycle

arr = []
for row in open("i1"):
    arr.append([x for x in row.strip()])
ELVES = set() 
for i,row in enumerate(arr):
    for j,v in enumerate(row):
        if v == "#":
            ELVES.add((i,j))


N = ((-1,0),((-1,1),(-1,0),(-1,-1)))
W = ((0,-1),((-1,-1),(0,-1),(1,-1)))
S = ((1,0),((1,1),(1,0),(1,-1)))
E = ((0,1),((-1,1),(0,1),(1,1)))

# Cycle move prio each round
D = ((N,S,W,E),(S,W,E,N),(W,E,N,S),(E,N,S,W))
it = cycle(D)
ROUND = 1

def ANY_ELF(ELVES,x,y):
    for dx in (-1,0,1):
        for dy in (-1,0,1):
            if dx == dy == 0:
                continue
            X = x+dx
            Y = y+dy
            if (x+dx,y+dy) in ELVES:
                return True
    return False

while True:
    moves = defaultdict(list)
    PRIO = next(it)
    for x,y in ELVES:
        if not ANY_ELF(ELVES,x,y):
            continue
        for K,V in PRIO:
            b = True
            for dx,dy in V:
                X = x+dxW
                Y = y+dy
                if (X,Y) in ELVES:
                    b = False
            if b:
                a,b = K
                moves[(x+a,y+b)].append((x,y))
                break

    any_moves = False
    for k,v in moves.items():
        if len(v) == 1:
            any_moves = True
            x,y = k
            i,j = v[0]
            ELVES.add((x,y))
            ELVES.remove((i,j))
    if not any_moves:
        print(ROUND)
        exit()

    if ROUND == 10:
        R = max((x[0] for x in ELVES))
        RMIN = min((x[0] for x in ELVES))
        C = max((x[1] for x in ELVES))
        CMIN = min((x[1] for x in ELVES))
        print(sum((x,y) not in ELVES for x in range(RMIN,R+1) for y in range(CMIN,C+1)))
    ROUND += 1
