arr = []
with open("i1") as file:
    for l in file:
        arr.append(int(l))

res = -1 
res2 = -1
cur = 0
cur2 = 0
for x in range(len(arr)-2):
    a,b,c = arr[x:x+3]
    s = a+b+c
    res += 1 if a > cur else 0
    res2 += 1 if s > cur2 else 0
    cur = a
    cur2 = s

print(res)
print(res2)
