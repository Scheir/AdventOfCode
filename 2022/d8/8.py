arr = []
for row in open("i1"):
    arr.append([int(x) for x in row.strip()])

res = 0
R,C = len(arr), len(arr[0])
for i,row in enumerate(arr):
    for j,cur in enumerate(row):
        cur = arr[i][j]
        if i == 0 or j == 0:
            res += 1
        else:
            col = [r[j] for r in arr]
            if all(w < cur for w in row[0:j]):
                res += 1
            elif all(w < cur for w in row[j+1:]):
                res += 1
            elif all(w < cur for w in col[0:i]):
                res += 1
            elif all(w < cur for w in col[i+1:]):
                res += 1
print(res)

#P2
res = 0
for i,row in enumerate(arr):
    for j,cur in enumerate(row):
        col = [r[j] for r in arr]
        left = row[0:j][::-1]
        right = row[j+1:]
        up = col[0:i][::-1]
        down = col[i+1:]
        a = next((i for i,x in enumerate(left,1) if x >= cur), len(left))
        b = next((i for i,x in enumerate(right,1) if x >= cur), len(right))
        c = next((i for i,x in enumerate(up,1) if x >= cur), len(up))
        d = next((i for i,x in enumerate(down,1) if x >= cur), len(down))
        res = max(res,a*b*c*d)
       
print(res)
