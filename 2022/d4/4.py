import re
arr = []
for row in open("i1"):
    arr.append((int(x) for x in re.findall("\d+", row)))

comp = lambda x: (len(x), x[0]) # If equal len, check first element
res = 0
res2 = 0
for a,b,c,d in arr:
    x = range(a,b+1)
    y = range(c,d+1)
    x,y = min(x,y,key=comp), max(x,y,key=comp)
    res += 1 if all(i in y for i in x) else 0
    res2 += 1 if any(i in y for i in x) else 0

print(res)
print(res2)
