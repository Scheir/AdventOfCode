from collections import *
from itertools import *
from functools import *
import re

arr = []
for l in open("i1"):
    l = l.strip()
    arr.append(l)

scores =  {")":3, "]":57, "}":1187, ">":25137}
scores2 = {"(":1, "[":2, "{":3, "<":4}

res = 0
res2 = [] 
for x in arr:
    q = deque()
    ok = True
    for y in x:
        if y in ("(","<","[","{"):
            q.append(y)
        else:
            p = q.pop()
            if y == ")":
                if p != "(":
                    res += scores[y]
                    ok = False
                    break
            elif y == "]":
                if p != "[":
                    res += scores[y]
                    ok = False
                    break
            elif y == "}":
                if p != "{":
                    res += scores[y]
                    ok = False
                    break
            elif y == ">":
                if p != "<":
                    res += scores[y]
                    ok = False
                    break
    temp_res = 0
    while q and ok:
        c = q.pop()
        temp_res *= 5
        temp_res += scores2[c]
    if ok:
        res2.append(temp_res)
        
print(res)
print(sorted(res2)[len(res2)//2])
