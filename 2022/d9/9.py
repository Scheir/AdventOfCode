arr = []
for row in open("i1"):
    a,b = row.split()
    arr.append((a,int(b)))    


def MOVE(head,tail):
    (x,y),(X,Y) = head,tail
    DX = abs(x-X)
    DY = abs(y-Y)
    if DX >= 2 and DY >= 2:
        X = x-1 if X < x else x+1
        Y = y-1 if Y < y else y+1
    elif DX >= 2:
        X = x-1 if X < x else x+1
        Y = y
    elif DY >= 2:
        X = x
        Y = y-1 if Y < y else y+1
    return (X,Y)


MOVES = {"U":(-1,0), "D":(1,0), "R":(0,1), "L":(0,-1)}
head = (0,0)
tail = (0,0)
seen = set()
for d,n in arr:
    for _ in range(n):
        X,Y = head
        dx,dy = MOVES.get(d)
        head = (X+dx,Y+dy)
        tail = MOVE(head,tail)
        seen.add(tail)

print(len(seen))

## P2
seen.clear()
ROPE = [(0,0) for _ in range(10)]
for d,n in arr:
    for _ in range(n):
        X,Y = ROPE[0] 
        dx,dy = MOVES.get(d)
        ROPE[0] = (X+dx,Y+dy)
        for i in range(1,len(ROPE)):
            ROPE[i] = MOVE(ROPE[i-1],ROPE[i])
        seen.add((ROPE[-1]))

print(len(seen))
