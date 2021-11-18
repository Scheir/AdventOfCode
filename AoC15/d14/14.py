arr = []
with open("i2") as file:
    for f in file:
        a,b,c,d = 0,3,6,13
        f = f.split()
        arr.append((f[a], int(f[b]), int(f[c]), int(f[d])))

res = []
const_val = 2503
for x in arr:
    a,b,c,d = x
    laps = const_val // (c+d) 
    rest = const_val % (c+d)
    dist = b*c*laps + min(rest,c)*b
    res.append(dist)

print(max(res))

mat = [[0]*(const_val+1) for x in range(len(arr))]
for x in range(const_val):
    for y in range(len(arr)):
        a,b,c,d = arr[y]
        if x % (c+d) < c:
            mat[y][x+1] = mat[y][x] + b
        else:
            mat[y][x+1] = mat[y][x]

res_arr = [0]*len(arr)
for x in range(1, len(mat[0])):
    lst = [r[x] for r in mat]
    cur_winner = 0
    for i in range(len(lst)):
        if lst[i] > cur_winner:
            cur_winner = lst[i]
    for i in range(len(lst)):
        if lst[i] == cur_winner:
            res_arr[i] += 1

print(max(res_arr))
