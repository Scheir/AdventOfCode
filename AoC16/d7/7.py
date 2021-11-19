import re
arr = []
with open("i1") as file:
    for l in file:
        arr.append(re.split("[\[\]]", l.rstrip()))

res = 0
for l in arr:
    bo = True
    be = False
    for i in range(len(l)):
        word = l[i]
        for x in range(len(word)-3):
            a,b,c,d = word[x:x+4]
            if a == d and b == c and a != b:
                if i % 2 == 0:
                    be = True
                else:
                    bo = False
    res += 1 if bo and be else 0
print(res)

res2 = 0
for l in arr:
    s = set()
    for i in range(0,len(l),2):
        word = l[i]
        for x in range(len(word)-2):
            a,b,c = word[x:x+3]
            if a == c and a != b:
                s.add(b+a+b)
    for i in range(1,len(l),2):
        word = l[i]
        for x in range(len(word)-2):
            w = word[x:x+3]
            if w in s:
                res2 += 1
                break

print(res2)
