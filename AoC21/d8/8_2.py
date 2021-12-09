import re
from collections import *
from functools import *
from itertools import permutations

inp = []
arr = []

for l in open("i1"):
    l = l.strip()
    a,b = l.split("|")
    arr.append(b.split())
    inp.append(a.split())

res = 0
for x in arr:
    for y in x:
        if len(y) in (2,3,4,7):
            res += 1

print(res)

digits = {
        0: 'abcefg',
        1: 'cf',
        2: 'acdeg',
        3: 'acdfg',
        4: 'bcdf',
        5: 'abdfg',
        6: 'abdefg',
        7: 'acf',
        8: 'abcdefg',
        9: 'abcdfg',
}

res = 0
for i, x in enumerate(inp):
    after = arr[i]
    for perm in permutations(list(range(8))):
        ok = True
        d = {}
        for j in range(8):
            d[chr(ord('a')+j)] = chr(ord('a')+perm[j])
        for word in x:
            permed_word = ""
            for y in word:
                permed_word += d[y]
            permed_word = ''.join(sorted(permed_word))
            if permed_word not in digits.values():
                ok = False
        if ok:
            break

    rd = ""
    for j in after:
        digit = ""
        for x in j:
            for k,v in d.items():
                if x == k:
                    digit+=v
            digit = ''.join(sorted(list(digit)))
        for k,v in digits.items():
            if v == digit:
                rd += str(k)
    print(rd)
    res += int(rd)

print(res)
