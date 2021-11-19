import re
from collections import Counter

def decrypt(word, num):
    res = ""
    for x in word:
        n = num % 26
        if x != '-':
            while n:
                if x == 'z':
                    x = 'a'
                else:
                    x = chr(ord(x)+1)
                n -= 1
        else:
            x = " "
        res += x
    return res

arr = []

with open("i1") as file:
    for l in file:
        a,b,c = re.match("(.*)-(\d+).(\w+).$", l).groups()
        arr.append((a,b,c))

res = 0
count = 0
for x in arr:
    word, num, order = x
    w = word.replace('-','')
    c = Counter(w)
    keys = sorted(c.keys())
    keys.sort(key=lambda x: -c[x]) 
    if ''.join(keys[:5]) == order:
        res += int(num)
        words = decrypt(word, int(num))
        if words == "northpole object storage":
            res2 = int(num)

print(res)
print(res2)
