with open("i1") as file:
    line = file.readline()
line = "><<"
xy = (0,0)
santa = (0,0)
robo = (0,0)
b = True
s = set()
s2 = set()
s.add(xy)
s2.add(robo)
for c in line:
    if b:
        xx,yy = santa
    else:
        xx,yy = robo
    x,y = xy
    if c == '^':
        x += 1
        xx += 1
    elif c == '>':
        y += 1
        yy += 1
    elif c == 'v':
        x -= 1
        xx -= 1
    elif c == '<':
        y -= 1
        yy -= 1
    xy = (x,y)
    s.add(xy)
    if b:
        santa = (xx,yy)
        s2.add(santa)
    else:
        robo = (xx,yy)
        s2.add(robo)
    b = not b
    print(santa, robo)

print(len(s))
print(len(s2))

