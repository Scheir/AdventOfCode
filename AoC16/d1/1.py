import re
arr = []
with open("i1") as file:
    for l in file:
        arr += re.findall("[LR]\d+",l.rstrip())

d = "^"
x,y = 0,0
s = set()
res2 = 0
for p in arr:
    a,b = p[0], int(p[1:]) 
    px, py = x, y
    if d == '^':
        x += -b if a == 'L' else b
        d = '<' if a == 'L' else '>'
    elif d == '<':
        y += -b if a == 'L' else b
        d = 'v' if a == 'L' else '^'
    elif d == 'v':
        x += b if a == 'L' else -b
        d = '>' if a == 'L' else '<'
    elif d == '>':
        y += b if a == 'L' else -b
        d = '^' if a == 'L' else 'v'
    if x == px:
        start, end = min(y,py), max(y,py)
        for i in range(start, end):
            if (x,i) in s and res2 == 0 and i != start:
                res2 = abs(x)+abs(i)
            else:
                s.add((x,i))
    else:
        start, end =  min(x,px), max(x,px)
        for i in range(start, end):
            if(i,y) in s and res2 == 0 and i != start:
                res2 = abs(i)+abs(y)
            else:
                s.add((i,y))

print(abs(x)+abs(y))
print(res2)

