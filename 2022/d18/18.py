from collections import deque
POINTS = set()
for row in open("i1"):
    a,b,c = [int(x) for x in row.strip().split(",")]
    POINTS.add((a,b,c))

DIR = ((1,0,0),(-1,0,0),(0,1,0),(0,-1,0),(0,0,1),(0,0,-1))

#Calculate surface
def get_surf(cubes):
    cnt = 0
    for x,y,z in cubes:
        for dx,dy,dz in DIR:
            if (x+dx,y+dy,z+dz) not in cubes:
                cnt += 1
    return cnt


p1 = get_surf(POINTS)

AIR = {} 
MX = 21
# Get all air cubes
for x in range(-1,MX):
    for y in range(-1,MX):
        for z in range(-1,MX):
            if (x,y,z) not in POINTS:
                AIR[(x,y,z)] = False


q = [(-1,-1,-1)]
seen = set()
# flood air cubes outside of interior
while q: #BFS
    x,y,z = q.pop()
    AIR[(x,y,z)] = True
    if (x,y,z) in seen:
        continue
    seen.add((x,y,z))
    for dx,dy,dz in DIR:
        X = x+dx
        Y = y+dy
        Z = z+dz
        if (X,Y,Z) in AIR and not AIR.get((X,Y,Z)):
            q.append((X,Y,Z))

# Check surface of interior air (pockets)
AIR = [(x,y,z) for (x,y,z),b in AIR.items() if not b]
p2 = get_surf(AIR)
print(p1)
print(p1-p2)
