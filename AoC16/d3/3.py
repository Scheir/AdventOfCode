arr = []
with open("i2") as file:
    for l in file:
        a,b,c = l.rstrip().split()
        arr.append((int(a),int(b),int(c)))

res = 0
for x in arr:
    l = sorted(list(x))
    a,b,c = l
    print(a,b,c)
    if a + b > c:
        res += 1
print(res)

flatarr = [r[i] for i in range(len(arr[0])) for r in arr]
res2 = 0
for x in range(0, len(flatarr), 3):
    a,b,c = sorted(flatarr[x:x+3])
    if a + b > c:
        res2 += 1

print(res2)
