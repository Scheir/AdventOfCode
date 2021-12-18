x1,x2= 96,125
y1,y2= -144,-98

res = 0
res2 = 0
for i in range(126):
    for j in range(-150, 300):
        x,y,dx,dy,maxy = 0,0,i,j,0
        for t in range(700):
            x += dx
            y += dy
            if dx > 0:
                dx -= 1 
            elif dx < 0:
                dx += 1 
            dy -= 1
            maxy = max(maxy,y)
            if x > x2:
                break
            if x1<=x<=x2 and y1<=y<=y2:
                res = max(res,maxy)
                res2 += 1
                print(i,j,maxy)
                break

print(res)
print(res2)
