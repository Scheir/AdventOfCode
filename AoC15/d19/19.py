import re
arr = []
d = {}
ma = 0
mi = 1000
with open("i1") as file:
    lines = list(file)
    for l in lines[:-2]:
        a,_,b = l.rstrip().split()
        arr.append((a,b))
        d[b] = a
        ma = ma if len(b) < ma else len(b)
        mi = mi if len(b) > mi else len(b)
    string = lines[-1].rstrip()

s = set()
for x in arr:
    a,b = x
    for i in range(len(string)):
        l = len(a)
        if string[i:i+l] == a:
            ts = string[0:i]+b+string[i+l:]
            s.add(ts)
print("Part1:",len(s))
keys = d.keys()
idx = 0
while string != "e":
    boolean = True
    for i in range(len(string)):
        for j in range(ma, mi-1, -1):
            reac = string[-i-j:len(string)-i]
            if reac in keys:
                pos = string.rfind(reac)
                string = string[:pos]+d[reac]+string[pos+len(reac):]
                boolean = False
                break
        if not boolean:
            break
    idx += 1
print("Part2:", idx)
