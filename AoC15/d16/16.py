import re
d = {"children": 3,
"cats": 7,
"samoyeds": 2,
"pomeranians": 3,
"akitas": 0,
"vizslas": 0,
"goldfish": 5,
"trees": 3,
"cars": 2,
"perfumes": 1,
}

lines = {}
lines_without_zero = {}
with open("i1") as file:
    for l in file:
        _,no,o1,c1,o2,c2,o3,c3 = re.split("[,:]?\s",l.rstrip())
        td = {o1:int(c1),o2:int(c2),o3:int(c3)}
        td2 = {}
        if c1 != '0':
            td2[o1] = int(c1)
        if c2 != '0':
            td2[o2] = int(c2)
        if c3 != '0':
            td2[o3] = int(c3)
        lines[no] = td
        lines_without_zero[no] = td2

(res,n) = (0,0)
for k in lines_without_zero:
    #print(lines_without_zero[k].items(), d.items())
    if lines_without_zero[k].items() <= d.items():
        count = len([key for key in lines_without_zero[k]])
        (res,n) = (count,k) if count > res else (res,n)
print(n)

for k in lines:#lines_without_zero:
    b = True
    for key in lines[k]:#lines_without_zero[k]:
        if key in ("cats", "trees"):
            if d[key] >= lines[k][key]:#lines_without_zero[k][key]:
                b = False
                break
        elif key in ("pomeranians","goldfish"):
            if d[key] <= lines[k][key]:#lines_without_zero[k][key]:
                b = False
                break
        else:
            if d[key] != lines[k][key]:#lines_without_zero[k][key]:
                b = False
                break
    if b:
        print(k)
        exit()
