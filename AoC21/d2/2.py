x,y = 0,0
xx,yy,aim = 0,0,0
for l in open("i1"):
    a,b = l.split()
    b = int(b)
    if a == "forward":
        x += b
        xx += b
        yy += aim*b
    elif a == "down":
        y += b
        aim += b
    else:
        y -= b
        aim -= b

print(x*y)
print(xx*yy)
