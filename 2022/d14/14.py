def solve(seen):
    cnt = 0 
    while True:
        x,y = 0,500
        while True: 
            # I have some weird bug somewhere
            # If x reaches 10000 we should have ended
            # long time ago...
            if x > 10000:
                return cnt
            if (x+1,y) not in seen:
                x += 1
            elif (x+1,y-1) not in seen:
                x += 1
                y -= 1
            elif (x+1,y+1) not in seen:
                x += 1
                y += 1
            else:
                seen.add((x,y))
                break
        if x == 0 and y == 500:
            cnt += 1
            break
        cnt += 1
    return cnt


arr = []
for x in open("i1"):
    arr.append(x.strip().split(" -> "))


seen = set()
maxy = 0
for row in arr:
    for a,b in zip(row,row[1:]):
        x0,y0 = [int(x) for x in a.split(",")]
        x1,y1 = [int(x) for x in b.split(",")]

        x0,x1 = min(x0,x1), max(x0,x1)
        y0,y1 = min(y0,y1), max(y0,y1)
        maxy = max(maxy,y1)
    
        for x in range(x0,x1+1):
            for y in range(y0,y1+1):
                seen.add((y,x))


seen2 = seen.copy()
for x in range(1000):
    seen2.add((maxy+2,x))

print(solve(seen))
print(solve(seen2))
