from functools import reduce
arr = []
for row in open("i1"):
    arr.append([int(x) for x in row.strip()])

DIR = ((1,0),(0,1),(-1,0),(0,-1))
res = 0
R,C = len(arr), len(arr[0])
for i,row in enumerate(arr):
    for j,cur in enumerate(row):
        if i == 0 or j == 0:
            res += 1
        else:
            ok = False 
            # Step in all directions one at a time
            # until we reach the end. If one dir is good
            # Ok is set to true
            for dx,dy in DIR:
                X = i+dx
                Y = j+dy
                b = True
                while 0<=X<R and 0<=Y<C:
                    if arr[X][Y] >= cur:
                        b = False
                    X += dx
                    Y += dy
                if b:
                    ok = True
            if ok:
                res += 1
print(res)

res = 0
for i, row in enumerate(arr):
    for j, cur in enumerate(row):
        if i in (0,R-1) or j in (0,C-1):
            continue
        cnts = []
        for dx,dy in DIR:
            X = i+dx
            Y = j+dy
            cnt = 0
            # Step in both directions and count trees all
            # trees, stop if you reach one this is equal big or bigger :D
            while 0<=X<R and 0<=Y<C:
                cnt += 1
                if arr[X][Y] >= cur:
                    break
                X += dx
                Y += dy
            cnts.append(cnt)
        res = max(res, reduce(lambda x,y: x*y,cnts))

print(res) 
