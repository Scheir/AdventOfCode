from functools import reduce
arr = []
with open("i1") as file:
    for line in file:
        arr.append(line.rstrip())

res = 0

ss = "HHELLOHHE"

bad = ("ab", "cd", "pq", "xy")
for l in arr:
    if reduce(lambda a,i: a+1 if i in ('a','e','i','o','u') else a, l, 0) >= 3:
        for x in range(len(l)-1):
            if l[x] == l[x+1]:
                if len([x for x in bad if x in l]) == 0:
                    res += 1
                break
print(res)

res = 0
for l in arr:
    ok = False
    for x in range(len(l)-2):
        a,c = l[x:x+3:2]
        if a == c:
            ok = True
            break
    if ok:
        for x in range(len(l)-1):
            s = str(l[x:x+2])
            if l.count(s) >= 2:
                res += 1
                break
print(res)
        
